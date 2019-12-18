#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fps_cfg {int f_mult; int /*<<< orphan*/  pict_fps_div; int /*<<< orphan*/  fps_div; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  pict_fps_divider; int /*<<< orphan*/  fps_divider; } ;
struct TYPE_6__ {TYPE_1__* reg_pat; } ;
struct TYPE_5__ {int line_length_pck; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int GROUPED_PARAMETER_HOLD ; 
 int GROUPED_PARAMETER_UPDATE ; 
 int /*<<< orphan*/  REG_GROUPED_PARAMETER_HOLD ; 
 int /*<<< orphan*/  REG_LINE_LENGTH_PCK ; 
 size_t RES_PREVIEW ; 
 TYPE_4__* mt9p012_client ; 
 TYPE_3__* mt9p012_ctrl ; 
 scalar_t__ mt9p012_i2c_write_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ mt9p012_regs ; 

__attribute__((used)) static int32_t mt9p012_set_fps(struct fps_cfg *fps)
{
	/* input is new fps in Q10 format */
	int32_t rc = 0;

	mt9p012_ctrl->fps_divider = fps->fps_div;
	mt9p012_ctrl->pict_fps_divider = fps->pict_fps_div;

	rc =
		mt9p012_i2c_write_w(mt9p012_client->addr,
			REG_GROUPED_PARAMETER_HOLD,
			GROUPED_PARAMETER_HOLD);
	if (rc < 0)
		return -EBUSY;

	rc =
		mt9p012_i2c_write_w(mt9p012_client->addr,
			REG_LINE_LENGTH_PCK,
			(mt9p012_regs.reg_pat[RES_PREVIEW].line_length_pck *
			fps->f_mult / 0x00000400));
	if (rc < 0)
		return rc;

	rc =
		mt9p012_i2c_write_w(mt9p012_client->addr,
			REG_GROUPED_PARAMETER_HOLD,
			GROUPED_PARAMETER_UPDATE);

	return rc;
}