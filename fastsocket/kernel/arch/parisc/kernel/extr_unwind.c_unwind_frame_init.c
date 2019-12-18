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
struct unwind_frame_info {int /*<<< orphan*/  ip; int /*<<< orphan*/  sp; int /*<<< orphan*/  r31; int /*<<< orphan*/  rp; struct task_struct* t; } ;
struct task_struct {scalar_t__ pid; } ;
struct pt_regs {int /*<<< orphan*/ * gr; int /*<<< orphan*/ * iaoq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct unwind_frame_info*,int /*<<< orphan*/ ,int) ; 

void unwind_frame_init(struct unwind_frame_info *info, struct task_struct *t, 
		       struct pt_regs *regs)
{
	memset(info, 0, sizeof(struct unwind_frame_info));
	info->t = t;
	info->sp = regs->gr[30];
	info->ip = regs->iaoq[0];
	info->rp = regs->gr[2];
	info->r31 = regs->gr[31];

	dbg("(%d) Start unwind from sp=%08lx ip=%08lx\n", 
	    t ? (int)t->pid : -1, info->sp, info->ip);
}