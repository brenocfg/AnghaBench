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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int prev_res; int curr_res; int sensormode; int /*<<< orphan*/  my_reg_line_count; int /*<<< orphan*/  my_reg_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
#define  S_FULL_SIZE 129 
#define  S_QTR_SIZE 128 
 int /*<<< orphan*/  S_RES_CAPTURE ; 
 int /*<<< orphan*/  S_RES_PREVIEW ; 
 int /*<<< orphan*/  S_UPDATE_PERIODIC ; 
 TYPE_1__* s5k3e2fx_ctrl ; 
 int /*<<< orphan*/  s5k3e2fx_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k3e2fx_write_exp_gain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t s5k3e2fx_video_config(int mode, int res)
{
	int32_t rc;

	switch (res) {
	case S_QTR_SIZE:
		rc = s5k3e2fx_setting(S_UPDATE_PERIODIC, S_RES_PREVIEW);
		if (rc < 0)
			return rc;

		CDBG("s5k3e2fx sensor configuration done!\n");
		break;

	case S_FULL_SIZE:
		rc = s5k3e2fx_setting(S_UPDATE_PERIODIC, S_RES_CAPTURE);
		if (rc < 0)
			return rc;

		break;

	default:
		return 0;
	} /* switch */

	s5k3e2fx_ctrl->prev_res = res;
	s5k3e2fx_ctrl->curr_res = res;
	s5k3e2fx_ctrl->sensormode = mode;

	rc =
		s5k3e2fx_write_exp_gain(s5k3e2fx_ctrl->my_reg_gain,
			s5k3e2fx_ctrl->my_reg_line_count);

	return rc;
}