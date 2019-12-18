#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int prev_res; int curr_res; int sensormode; int /*<<< orphan*/  my_reg_line_count; int /*<<< orphan*/  my_reg_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
#define  FULL_SIZE 129 
 int /*<<< orphan*/  MT9P012_REG_RESET_REGISTER ; 
#define  QTR_SIZE 128 
 int /*<<< orphan*/  RES_CAPTURE ; 
 int /*<<< orphan*/  RES_PREVIEW ; 
 int /*<<< orphan*/  UPDATE_PERIODIC ; 
 TYPE_2__* mt9p012_client ; 
 TYPE_1__* mt9p012_ctrl ; 
 int /*<<< orphan*/  mt9p012_i2c_write_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt9p012_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9p012_write_exp_gain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t mt9p012_video_config(int mode, int res)
{
	int32_t rc;

	switch (res) {
	case QTR_SIZE:
		rc = mt9p012_setting(UPDATE_PERIODIC, RES_PREVIEW);
		if (rc < 0)
			return rc;

		CDBG("mt9p012 sensor configuration done!\n");
		break;

	case FULL_SIZE:
		rc =
		mt9p012_setting(UPDATE_PERIODIC, RES_CAPTURE);
		if (rc < 0)
			return rc;

		break;

	default:
		return 0;
	} /* switch */

	mt9p012_ctrl->prev_res = res;
	mt9p012_ctrl->curr_res = res;
	mt9p012_ctrl->sensormode = mode;

	rc =
		mt9p012_write_exp_gain(mt9p012_ctrl->my_reg_gain,
			mt9p012_ctrl->my_reg_line_count);

	rc =
		mt9p012_i2c_write_w(mt9p012_client->addr,
			MT9P012_REG_RESET_REGISTER,
			0x10cc|0x0002);

	return rc;
}