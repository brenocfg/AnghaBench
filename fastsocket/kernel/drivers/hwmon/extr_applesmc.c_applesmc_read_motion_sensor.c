#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int s16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MOTION_SENSOR_X_KEY ; 
 int /*<<< orphan*/  MOTION_SENSOR_Y_KEY ; 
 int /*<<< orphan*/  MOTION_SENSOR_Z_KEY ; 
#define  SENSOR_X 130 
#define  SENSOR_Y 129 
#define  SENSOR_Z 128 
 int applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int applesmc_read_motion_sensor(int index, s16* value)
{
	u8 buffer[2];
	int ret;

	switch (index) {
	case SENSOR_X:
		ret = applesmc_read_key(MOTION_SENSOR_X_KEY, buffer, 2);
		break;
	case SENSOR_Y:
		ret = applesmc_read_key(MOTION_SENSOR_Y_KEY, buffer, 2);
		break;
	case SENSOR_Z:
		ret = applesmc_read_key(MOTION_SENSOR_Z_KEY, buffer, 2);
		break;
	default:
		ret = -EINVAL;
	}

	*value = ((s16)buffer[0] << 8) | buffer[1];

	return ret;
}