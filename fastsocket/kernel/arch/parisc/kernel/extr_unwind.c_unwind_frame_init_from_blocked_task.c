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
struct unwind_frame_info {int dummy; } ;
struct pt_regs {int /*<<< orphan*/  kpc; int /*<<< orphan*/ * iaoq; int /*<<< orphan*/  ksp; int /*<<< orphan*/ * gr; } ;
struct TYPE_2__ {struct pt_regs regs; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct pt_regs*) ; 
 struct pt_regs* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unwind_frame_init (struct unwind_frame_info*,struct task_struct*,struct pt_regs*) ; 

void unwind_frame_init_from_blocked_task(struct unwind_frame_info *info, struct task_struct *t)
{
	struct pt_regs *r = &t->thread.regs;
	struct pt_regs *r2;

	r2 = kmalloc(sizeof(struct pt_regs), GFP_ATOMIC);
	if (!r2)
		return;
	*r2 = *r;
	r2->gr[30] = r->ksp;
	r2->iaoq[0] = r->kpc;
	unwind_frame_init(info, t, r2);
	kfree(r2);
}