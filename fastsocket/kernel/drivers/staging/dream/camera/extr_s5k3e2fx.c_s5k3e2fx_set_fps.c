#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fps_cfg {int fps_div; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int fps_divider; } ;
struct TYPE_4__ {int size_h; int blk_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_FRAME_LENGTH_LINES_LSB ; 
 int /*<<< orphan*/  REG_FRAME_LENGTH_LINES_MSB ; 
 size_t S_RES_PREVIEW ; 
 TYPE_3__* s5k3e2fx_client ; 
 TYPE_2__* s5k3e2fx_ctrl ; 
 scalar_t__ s5k3e2fx_i2c_write_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* s5k3e2fx_reg_pat ; 

__attribute__((used)) static int32_t s5k3e2fx_set_fps(struct fps_cfg *fps)
{
	/* input is new fps in Q10 format */
	int32_t rc = 0;

	s5k3e2fx_ctrl->fps_divider = fps->fps_div;

	rc = s5k3e2fx_i2c_write_b(s5k3e2fx_client->addr,
		REG_FRAME_LENGTH_LINES_MSB,
		(((s5k3e2fx_reg_pat[S_RES_PREVIEW].size_h +
			s5k3e2fx_reg_pat[S_RES_PREVIEW].blk_l) *
			s5k3e2fx_ctrl->fps_divider / 0x400) & 0xFF00) >> 8);
	if (rc < 0)
		goto set_fps_done;

	rc = s5k3e2fx_i2c_write_b(s5k3e2fx_client->addr,
		REG_FRAME_LENGTH_LINES_LSB,
		(((s5k3e2fx_reg_pat[S_RES_PREVIEW].size_h +
			s5k3e2fx_reg_pat[S_RES_PREVIEW].blk_l) *
			s5k3e2fx_ctrl->fps_divider / 0x400) & 0xFF00));

set_fps_done:
	return rc;
}