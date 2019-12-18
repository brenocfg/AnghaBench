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
struct mdp_regs {int op; } ;
struct TYPE_4__ {size_t format; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;
struct mdp_blit_req {scalar_t__ transp_mask; int alpha; TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 scalar_t__ HAS_ALPHA (int /*<<< orphan*/ ) ; 
 int MDP_ALPHA_NOP ; 
 scalar_t__ MDP_TRANSP_NOP ; 
 int PPP_BLEND_ALPHA_TRANSP ; 
 int PPP_OP_BLEND_ALPHA_BLEND_NORMAL ; 
 int PPP_OP_BLEND_CONSTANT_ALPHA ; 
 int PPP_OP_BLEND_ON ; 
 int PPP_OP_BLEND_SRCPIXEL_ALPHA ; 
 int PPP_OP_BLEND_SRCPIXEL_TRANSP ; 
 int PPP_OP_ROT_ON ; 
 int* bg_op_chroma ; 
 scalar_t__ transp_convert (struct mdp_blit_req*) ; 

__attribute__((used)) static void blit_blend(struct mdp_blit_req *req, struct mdp_regs *regs)
{
	/* TRANSP BLEND */
	if (req->transp_mask != MDP_TRANSP_NOP) {
		req->transp_mask = transp_convert(req);
		if (req->alpha != MDP_ALPHA_NOP) {
			/* use blended transparancy mode
			 * pixel = (src == transp) ? dst : blend
			 * blend is combo of blend_eq_sel and
			 * blend_alpha_sel */
			regs->op |= PPP_OP_ROT_ON | PPP_OP_BLEND_ON |
				PPP_OP_BLEND_ALPHA_BLEND_NORMAL |
				PPP_OP_BLEND_CONSTANT_ALPHA |
				PPP_BLEND_ALPHA_TRANSP;
		} else {
			/* simple transparancy mode
			 * pixel = (src == transp) ? dst : src */
			regs->op |= PPP_OP_ROT_ON | PPP_OP_BLEND_ON |
				PPP_OP_BLEND_SRCPIXEL_TRANSP;
		}
	}

	req->alpha &= 0xff;
	/* ALPHA BLEND */
	if (HAS_ALPHA(req->src.format)) {
		regs->op |= PPP_OP_ROT_ON | PPP_OP_BLEND_ON |
			PPP_OP_BLEND_SRCPIXEL_ALPHA;
	} else if (req->alpha < MDP_ALPHA_NOP) {
		/* just blend by alpha */
		regs->op |= PPP_OP_ROT_ON | PPP_OP_BLEND_ON |
			PPP_OP_BLEND_ALPHA_BLEND_NORMAL |
			PPP_OP_BLEND_CONSTANT_ALPHA;
	}

	regs->op |= bg_op_chroma[req->dst.format];
}