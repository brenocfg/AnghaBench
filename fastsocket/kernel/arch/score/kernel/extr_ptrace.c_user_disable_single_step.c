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
struct TYPE_2__ {int insn1_type; int ss_nextcnt; int insn2_type; scalar_t__ single_step; int /*<<< orphan*/  insn2; int /*<<< orphan*/  addr2; int /*<<< orphan*/  insn1; int /*<<< orphan*/  addr1; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_tsk_long (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tsk_short (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void user_disable_single_step(struct task_struct *child)
{
	if (child->thread.insn1_type == 0)
		write_tsk_short(child, child->thread.addr1,
				child->thread.insn1);

	if (child->thread.insn1_type == 1)
		write_tsk_long(child, child->thread.addr1,
				child->thread.insn1);

	if (child->thread.ss_nextcnt == 2) {	/* branch */
		if (child->thread.insn1_type == 0)
			write_tsk_short(child, child->thread.addr1,
					child->thread.insn1);
		if (child->thread.insn1_type == 1)
			write_tsk_long(child, child->thread.addr1,
					child->thread.insn1);
		if (child->thread.insn2_type == 0)
			write_tsk_short(child, child->thread.addr2,
					child->thread.insn2);
		if (child->thread.insn2_type == 1)
			write_tsk_long(child, child->thread.addr2,
					child->thread.insn2);
	}

	child->thread.single_step = 0;
	child->thread.ss_nextcnt = 0;
}