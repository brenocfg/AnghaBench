#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  CAMERA_EFFECT_MONO 137 
#define  CAMERA_EFFECT_MOSAIC 136 
#define  CAMERA_EFFECT_NEGATIVE 135 
#define  CAMERA_EFFECT_OFF 134 
#define  CAMERA_EFFECT_PASTEL 133 
#define  CAMERA_EFFECT_RESIZE 132 
#define  CAMERA_EFFECT_SEPIA 131 
#define  CAMERA_EFFECT_SOLARIZE 130 
 long EINVAL ; 
#define  SENSOR_PREVIEW_MODE 129 
#define  SENSOR_SNAPSHOT_MODE 128 
 int /*<<< orphan*/  WORD_LEN ; 
 TYPE_1__* mt9d112_client ; 
 long mt9d112_i2c_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long mt9d112_set_effect(int mode, int effect)
{
	uint16_t reg_addr;
	uint16_t reg_val;
	long rc = 0;

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		/* Context A Special Effects */
		reg_addr = 0x2799;
		break;

	case SENSOR_SNAPSHOT_MODE:
		/* Context B Special Effects */
		reg_addr = 0x279B;
		break;

	default:
		reg_addr = 0x2799;
		break;
	}

	switch (effect) {
	case CAMERA_EFFECT_OFF: {
		reg_val = 0x6440;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x338C, reg_addr, WORD_LEN);
		if (rc < 0)
			return rc;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x3390, reg_val, WORD_LEN);
		if (rc < 0)
			return rc;
	}
			break;

	case CAMERA_EFFECT_MONO: {
		reg_val = 0x6441;
		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x338C, reg_addr, WORD_LEN);
		if (rc < 0)
			return rc;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x3390, reg_val, WORD_LEN);
		if (rc < 0)
			return rc;
	}
		break;

	case CAMERA_EFFECT_NEGATIVE: {
		reg_val = 0x6443;
		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x338C, reg_addr, WORD_LEN);
		if (rc < 0)
			return rc;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x3390, reg_val, WORD_LEN);
		if (rc < 0)
			return rc;
	}
		break;

	case CAMERA_EFFECT_SOLARIZE: {
		reg_val = 0x6445;
		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x338C, reg_addr, WORD_LEN);
		if (rc < 0)
			return rc;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x3390, reg_val, WORD_LEN);
		if (rc < 0)
			return rc;
	}
		break;

	case CAMERA_EFFECT_SEPIA: {
		reg_val = 0x6442;
		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x338C, reg_addr, WORD_LEN);
		if (rc < 0)
			return rc;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x3390, reg_val, WORD_LEN);
		if (rc < 0)
			return rc;
	}
		break;

	case CAMERA_EFFECT_PASTEL:
	case CAMERA_EFFECT_MOSAIC:
	case CAMERA_EFFECT_RESIZE:
		return -EINVAL;

	default: {
		reg_val = 0x6440;
		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x338C, reg_addr, WORD_LEN);
		if (rc < 0)
			return rc;

		rc = mt9d112_i2c_write(mt9d112_client->addr,
			0x3390, reg_val, WORD_LEN);
		if (rc < 0)
			return rc;

		return -EINVAL;
	}
	}

	/* Refresh Sequencer */
	rc = mt9d112_i2c_write(mt9d112_client->addr,
		0x338C, 0xA103, WORD_LEN);
	if (rc < 0)
		return rc;

	rc = mt9d112_i2c_write(mt9d112_client->addr,
		0x3390, 0x0005, WORD_LEN);

	return rc;
}