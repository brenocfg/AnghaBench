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
typedef  int uint32_t ;
struct mdp_regs {int phasex_init; int phasey_init; int phasex_step; int phasey_step; int op; } ;
struct mdp_info {int dummy; } ;
struct TYPE_4__ {int w; int h; } ;
struct TYPE_3__ {int h; int w; } ;
struct mdp_blit_req {int flags; TYPE_2__ src_rect; TYPE_1__ dst_rect; } ;

/* Variables and functions */
 int MDP_BLUR ; 
 int MDP_DOWNSCALE_PT2TOPT4 ; 
 int MDP_DOWNSCALE_PT4TOPT6 ; 
 int MDP_DOWNSCALE_PT6TOPT8 ; 
 int MDP_DOWNSCALE_PT8TO1 ; 
 int MDP_ROT_90 ; 
 int PPP_OP_SCALE_X_ON ; 
 int PPP_OP_SCALE_Y_ON ; 
 int downscale_x_table ; 
 int downscale_y_table ; 
 int /*<<< orphan*/  load_scale_table (struct mdp_info const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mdp_downscale_x_table ; 
 int /*<<< orphan*/ * mdp_downscale_y_table ; 
 scalar_t__ scale_params (int,int,int,int*,int*) ; 

__attribute__((used)) static int blit_scale(const struct mdp_info *mdp, struct mdp_blit_req *req,
		      struct mdp_regs *regs)
{
	uint32_t phase_init_x, phase_init_y, phase_step_x, phase_step_y;
	uint32_t scale_factor_x, scale_factor_y;
	uint32_t downscale;
	uint32_t dst_w, dst_h;

	if (req->flags & MDP_ROT_90) {
		dst_w = req->dst_rect.h;
		dst_h = req->dst_rect.w;
	} else {
		dst_w = req->dst_rect.w;
		dst_h = req->dst_rect.h;
	}
	if ((req->src_rect.w == dst_w)  && (req->src_rect.h == dst_h) &&
	    !(req->flags & MDP_BLUR)) {
		regs->phasex_init = 0;
		regs->phasey_init = 0;
		regs->phasex_step = 0;
		regs->phasey_step = 0;
		return 0;
	}

	if (scale_params(req->src_rect.w, dst_w, 1, &phase_init_x,
			 &phase_step_x) ||
	    scale_params(req->src_rect.h, dst_h, 1, &phase_init_y,
			 &phase_step_y))
		return -1;

	scale_factor_x = (dst_w * 10) / req->src_rect.w;
	scale_factor_y = (dst_h * 10) / req->src_rect.h;

	if (scale_factor_x > 8)
		downscale = MDP_DOWNSCALE_PT8TO1;
	else if (scale_factor_x > 6)
		downscale = MDP_DOWNSCALE_PT6TOPT8;
	else if (scale_factor_x > 4)
		downscale = MDP_DOWNSCALE_PT4TOPT6;
	else
		downscale = MDP_DOWNSCALE_PT2TOPT4;
	if (downscale != downscale_x_table) {
		load_scale_table(mdp, mdp_downscale_x_table[downscale], 64);
		downscale_x_table = downscale;
	}

	if (scale_factor_y > 8)
		downscale = MDP_DOWNSCALE_PT8TO1;
	else if (scale_factor_y > 6)
		downscale = MDP_DOWNSCALE_PT6TOPT8;
	else if (scale_factor_y > 4)
		downscale = MDP_DOWNSCALE_PT4TOPT6;
	else
		downscale = MDP_DOWNSCALE_PT2TOPT4;
	if (downscale != downscale_y_table) {
		load_scale_table(mdp, mdp_downscale_y_table[downscale], 64);
		downscale_y_table = downscale;
	}

	regs->phasex_init = phase_init_x;
	regs->phasey_init = phase_init_y;
	regs->phasex_step = phase_step_x;
	regs->phasey_step = phase_step_y;
	regs->op |= (PPP_OP_SCALE_Y_ON | PPP_OP_SCALE_X_ON);
	return 0;

}