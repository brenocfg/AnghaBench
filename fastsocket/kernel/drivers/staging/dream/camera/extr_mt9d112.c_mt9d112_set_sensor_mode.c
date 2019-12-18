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
 long EINVAL ; 
#define  SENSOR_PREVIEW_MODE 129 
#define  SENSOR_SNAPSHOT_MODE 128 
 int /*<<< orphan*/  WORD_LEN ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* mt9d112_client ; 
 long mt9d112_i2c_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long mt9d112_set_sensor_mode(int mode)
{
	uint16_t clock;
	long rc = 0;

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x338C, 0xA20C, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x3390, 0x0004, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x338C, 0xA215, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x3390, 0x0004, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x338C, 0xA20B, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x3390, 0x0000, WORD_LEN);
		if (rc < 0)
			return rc;

		clock = 0x0250;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x341C, clock, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x338C, 0xA103, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x3390, 0x0001, WORD_LEN);
		if (rc < 0)
			return rc;

		mdelay(5);
		break;

	case SENSOR_SNAPSHOT_MODE:
		/* Switch to lower fps for Snapshot */
		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x341C, 0x0120, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x338C, 0xA120, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x3390, 0x0002, WORD_LEN);
		if (rc < 0)
			return rc;

		mdelay(5);

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x338C, 0xA103, WORD_LEN);
		if (rc < 0)
			return rc;

		rc =
			mt9d112_i2c_write(mt9d112_client->addr,
				0x3390, 0x0002, WORD_LEN);
		if (rc < 0)
			return rc;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}