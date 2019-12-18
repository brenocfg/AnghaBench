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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  GROUPED_PARAMETER_HOLD ; 
 int /*<<< orphan*/  GROUPED_PARAMETER_UPDATE ; 
 int /*<<< orphan*/  REG_GROUPED_PARAMETER_HOLD ; 
#define  SENSOR_PREVIEW_MODE 130 
#define  SENSOR_RAW_SNAPSHOT_MODE 129 
#define  SENSOR_SNAPSHOT_MODE 128 
 TYPE_1__* mt9t013_client ; 
 scalar_t__ mt9t013_i2c_write_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt9t013_raw_snapshot_config (int) ; 
 scalar_t__ mt9t013_snapshot_config (int) ; 
 scalar_t__ mt9t013_video_config (int,int) ; 

__attribute__((used)) static int32_t mt9t013_set_sensor_mode(int mode, int res)
{
	int32_t rc = 0;
	rc = mt9t013_i2c_write_w(mt9t013_client->addr,
			REG_GROUPED_PARAMETER_HOLD,
			GROUPED_PARAMETER_HOLD);
	if (rc < 0)
		return rc;

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		rc = mt9t013_video_config(mode, res);
		break;

	case SENSOR_SNAPSHOT_MODE:
		rc = mt9t013_snapshot_config(mode);
		break;

	case SENSOR_RAW_SNAPSHOT_MODE:
		rc = mt9t013_raw_snapshot_config(mode);
		break;

	default:
		return -EINVAL;
	}

	/* FIXME: what should we do if rc < 0? */
	if (rc >= 0)
		return mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_GROUPED_PARAMETER_HOLD,
				GROUPED_PARAMETER_UPDATE);
	return rc;
}