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
struct mdp_regs {int /*<<< orphan*/  op; } ;
struct mdp_blit_req {int flags; } ;

/* Variables and functions */
 int MDP_FLIP_LR ; 
 int MDP_FLIP_UD ; 
 int MDP_ROT_90 ; 
 int MDP_ROT_NOP ; 
 int /*<<< orphan*/  PPP_OP_FLIP_LR ; 
 int /*<<< orphan*/  PPP_OP_FLIP_UD ; 
 int /*<<< orphan*/  PPP_OP_ROT_90 ; 
 int /*<<< orphan*/  PPP_OP_ROT_ON ; 
 int /*<<< orphan*/  rotate_dst_addr_x (struct mdp_blit_req*,struct mdp_regs*) ; 
 int /*<<< orphan*/  rotate_dst_addr_y (struct mdp_blit_req*,struct mdp_regs*) ; 

__attribute__((used)) static void blit_rotate(struct mdp_blit_req *req,
			struct mdp_regs *regs)
{
	if (req->flags == MDP_ROT_NOP)
		return;

	regs->op |= PPP_OP_ROT_ON;
	if ((req->flags & MDP_ROT_90 || req->flags & MDP_FLIP_LR) &&
	    !(req->flags & MDP_ROT_90 && req->flags & MDP_FLIP_LR))
		rotate_dst_addr_x(req, regs);
	if (req->flags & MDP_ROT_90)
		regs->op |= PPP_OP_ROT_90;
	if (req->flags & MDP_FLIP_UD) {
		regs->op |= PPP_OP_FLIP_UD;
		rotate_dst_addr_y(req, regs);
	}
	if (req->flags & MDP_FLIP_LR)
		regs->op |= PPP_OP_FLIP_LR;
}