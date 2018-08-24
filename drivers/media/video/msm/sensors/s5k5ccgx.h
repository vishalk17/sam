/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __S5K5CCGX_H__
#define __S5K5CCGX_H__

#include "msm_sensor.h"
#define SENSOR_NAME "s5k5ccgx"
#define PLATFORM_DRIVER_NAME "msm_camera_s5k5ccgx"
#define s5k5ccgx_obj s5k5ccgx_##obj

#include <linux/types.h>
#include <mach/board.h>

#undef CONFIG_LOAD_FILE
/*#define CONFIG_LOAD_FILE*/

#undef DEBUG_LEVEL_HIGH
#undef DEBUG_LEVEL_MID
#define DEBUG_LEVEL_HIGH
/*#define DEBUG_LEVEL_MID */

#if defined(DEBUG_LEVEL_HIGH)
#define CAM_DEBUG(fmt, arg...)	\
	do {					\
		printk(KERN_DEBUG "[%s:%d] " fmt,	\
			__func__, __LINE__, ##arg);	\
	}						\
	while (0)

#define cam_info(fmt, arg...)			\
	do {					\
		printk(KERN_INFO "[%s:%d] " fmt,	\
			__func__, __LINE__, ##arg);	\
	}						\
	while (0)
#elif defined(DEBUG_LEVEL_MID)
#define CAM_DEBUG(fmt, arg...)
#define cam_info(fmt, arg...)			\
	do {					\
		printk(KERN_INFO "[%s:%d] " fmt,	\
			__func__, __LINE__, ##arg);	\
	}						\
	while (0)
#else
#define CAM_DEBUG(fmt, arg...)
#define cam_info(fmt, arg...)
#endif

#undef DEBUG_CAM_I2C
#define DEBUG_CAM_I2C

#if defined(DEBUG_CAM_I2C)
#define cam_i2c_dbg(fmt, arg...)		\
	do {					\
		printk(KERN_DEBUG "[%s:%d] " fmt,	\
			__func__, __LINE__, ##arg);	\
	}						\
	while (0)
#else
#define cam_i2c_dbg(fmt, arg...)
#endif


#define cam_err(fmt, arg...)	\
	do {					\
		printk(KERN_ERR "[%s:%d] " fmt,		\
			__func__, __LINE__, ##arg);	\
	}						\
	while (0)

#define S5K5CCGX_DELAY_RETRIES 100/*for modesel_fix, awbsts, half_move_sts*/

#define FLASH_PULSE_CNT 2

#define ERROR 1

#define IN_AUTO_MODE 1
#define IN_MACRO_MODE 2

#define S5K5CCGX_BURST_DATA_LENGTH 2700

#define WAIT_1MS 1000
#define WAIT_10MS 10000
#define I2C_RETRY_CNT 5

#define S5K5CCGX_WRITE_LIST(A)	\
	s5k5ccgx_i2c_write_list(A, (sizeof(A) / sizeof(A[0])), #A)

struct s5k5ccgx_userset {
	//unsigned int	focus_mode; not supported
	//unsigned int	focus_status; not supported
	//unsigned int	continuous_af; nt supported

	unsigned int	metering;
	unsigned int	exposure;
	unsigned int	wb;
	unsigned int	iso;
	int				contrast;
	int				saturation;
	int				sharpness;
	int				brightness;
	int				ev;
	int				scene;
	unsigned int	zoom;
	unsigned int	effect;		/* Color FX (AKA Color tone) */
	unsigned int	scenemode;
	unsigned int	detectmode;
	unsigned int	antishake;
	unsigned int	fps;
	//unsigned int	flash_mode; not supported
	//unsigned int	flash_state; not supported
	unsigned int	stabilize;	/* IS */
	unsigned int	strobe;
	unsigned int	jpeg_quality;
	/*unsigned int preview_size;*/
	unsigned int	preview_size_idx;
	unsigned int	capture_size;
	unsigned int	thumbnail_size;
};

struct s5k5ccgx_exif_data {
	unsigned short iso;
	unsigned short shutterspeed;
};

struct s5k5ccgx_ctrl {
	const struct msm_camera_sensor_info *sensordata;
	struct s5k5ccgx_userset settings;
	struct msm_camera_i2c_client *sensor_i2c_client;
	struct msm_sensor_ctrl_t *s_ctrl;
	struct v4l2_subdev *sensor_dev;
	struct v4l2_subdev sensor_v4l2_subdev;
	struct v4l2_subdev_info *sensor_v4l2_subdev_info;
	uint8_t sensor_v4l2_subdev_info_size;
	struct v4l2_subdev_ops *sensor_v4l2_subdev_ops;

	int op_mode;
	int cam_mode;
	int vtcall_mode;
	int started;
	//int flash_mode; not supported
	int lowLight;
	int dtpTest;
	//int af_mode; not supported
	//int af_status; not supported
	unsigned int lux;
	int awb_mode;
	int samsungapp;
};

struct s5k5ccgx_format {
	enum v4l2_mbus_pixelcode code;
	enum v4l2_colorspace colorspace;
	u16 fmt;
	u16 order;
};

struct s5k5ccgx_i2c_reg_conf {
	unsigned short waddr;
	unsigned short wdata;
};

/* preview size idx*/
enum s5k5ccgx_preview_size_t {
	PREVIEW_SIZE_VGA = 0,			/* 640x480 */
	PREVIEW_SIZE_WVGA,			/* 800x480 */
	PREVIEW_SIZE_HD,				/* 1280x720 */
	PREVIEW_SIZE_HD_DISABLE,		/* 1280x720 DISABLE */
	PREVIEW_SIZE_W960,			/* 960x720 */
	PREVIEW_SIZE_QCIF,		/* 176x144 */
	PREVIEW_SIZE_720_D1 = 6		/* 720x480 */

};

/* DTP */
enum s5k5ccgx_dtp_t {
	DTP_OFF = 0,
	DTP_ON,
	DTP_OFF_ACK,
	DTP_ON_ACK,
};

enum s5k5ccgx_camera_mode_t {
	PREVIEW_MODE = 0,
	MOVIE_MODE
};

enum isx02_AF_mode_t {
	SHUTTER_AF_MODE = 0,
	TOUCH_AF_MODE
};

enum s5k5ccgx_flash_mode_t {
	FLASH_OFF = 0,
	CAPTURE_FLASH,
	MOVIE_FLASH,
};

enum s5k5ccgx_resolution_t {
	QTR_SIZE,
	FULL_SIZE,
	INVALID_SIZE
};

enum s5k5ccgx_setting {
	RES_PREVIEW,
	RES_CAPTURE
};

enum s5k5ccgx_reg_update {
	/* Sensor egisters that need to be updated during initialization */
	REG_INIT,
	/* Sensor egisters that needs periodic I2C writes */
	UPDATE_PERIODIC,
	/* All the sensor Registers will be updated */
	UPDATE_ALL,
	/* Not valid update */
	UPDATE_INVALID
};
/*
struct s5k5ccgx_reg {
	const struct reg_struct_init  *reg_pat_init;
	const struct reg_struct  *reg_pat;
};
*/

//u8 torchonoff;

static bool g_bCameraRunning;
static unsigned int config_csi2;
static bool changedPreviewSize = false;


static struct s5k5ccgx_ctrl s5k5ccgx_control;
static struct i2c_client *s5k5ccgx_client;
static struct s5k5ccgx_exif_data s5k5ccgx_exif;
static struct msm_sensor_ctrl_t s5k5ccgx_s_ctrl;
static struct device s5k5ccgx_dev;

static DECLARE_WAIT_QUEUE_HEAD(s5k5ccgx_wait_queue);
void sensor_native_control(void __user *arg);
static int s5k5ccgx_sensor_config(struct msm_sensor_ctrl_t *s_ctrl,
	void __user *argp);
static int s5k5ccgx_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id);
static int s5k5ccgx_regs_table_write(char *name);
DEFINE_MUTEX(s5k5ccgx_mut);

#endif /* __S5K5CCGX_H__ */
