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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp_regs {int dst0; int dst_bpp; int dst1; } ;
struct TYPE_2__ {int w; } ;
struct mdp_blit_req {TYPE_1__ dst_rect; } ;

/* Variables and functions */
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rotate_dst_addr_x(struct mdp_blit_req *req, struct mdp_regs *regs)
{
	regs->dst0 += (req->dst_rect.w -
		       min((uint32_t)16, req->dst_rect.w)) * regs->dst_bpp;
	regs->dst1 += (req->dst_rect.w -
		       min((uint32_t)16, req->dst_rect.w)) * regs->dst_bpp;
}