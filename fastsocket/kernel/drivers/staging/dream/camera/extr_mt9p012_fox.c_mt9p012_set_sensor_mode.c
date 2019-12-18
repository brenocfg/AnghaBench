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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SENSOR_PREVIEW_MODE 130 
#define  SENSOR_RAW_SNAPSHOT_MODE 129 
#define  SENSOR_SNAPSHOT_MODE 128 
 int /*<<< orphan*/  mt9p012_raw_snapshot_config (int) ; 
 int /*<<< orphan*/  mt9p012_snapshot_config (int) ; 
 int /*<<< orphan*/  mt9p012_video_config (int,int) ; 

__attribute__((used)) static int32_t mt9p012_set_sensor_mode(int mode, int res)
{
	int32_t rc = 0;

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		rc = mt9p012_video_config(mode, res);
		break;

	case SENSOR_SNAPSHOT_MODE:
		rc = mt9p012_snapshot_config(mode);
		break;

	case SENSOR_RAW_SNAPSHOT_MODE:
		rc = mt9p012_raw_snapshot_config(mode);
		break;

	default:
		rc = -EINVAL;
		break;
	}

	return rc;
}