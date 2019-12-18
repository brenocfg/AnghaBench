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
struct TYPE_4__ {scalar_t__ format; } ;
struct TYPE_3__ {scalar_t__ format; } ;
struct mdp_blit_req {TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 scalar_t__ IS_RGB (scalar_t__) ; 
 scalar_t__ IS_YCRCB (scalar_t__) ; 
 scalar_t__ MDP_RGB_565 ; 
 int PPP_OP_CONVERT_MATRIX_SECONDARY ; 
 int PPP_OP_CONVERT_ON ; 
 int PPP_OP_CONVERT_RGB2YCBCR ; 
 int PPP_OP_CONVERT_YCBCR2RGB ; 

__attribute__((used)) static void blit_convert(struct mdp_blit_req *req, struct mdp_regs *regs)
{
	if (req->src.format == req->dst.format)
		return;
	if (IS_RGB(req->src.format) && IS_YCRCB(req->dst.format)) {
		regs->op |= PPP_OP_CONVERT_RGB2YCBCR | PPP_OP_CONVERT_ON;
	} else if (IS_YCRCB(req->src.format) && IS_RGB(req->dst.format)) {
		regs->op |= PPP_OP_CONVERT_YCBCR2RGB | PPP_OP_CONVERT_ON;
		if (req->dst.format == MDP_RGB_565)
			regs->op |= PPP_OP_CONVERT_MATRIX_SECONDARY;
	}
}