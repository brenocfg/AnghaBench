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
struct TYPE_3__ {int /*<<< orphan*/  fr; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;
struct task_struct {TYPE_2__ thread; } ;
typedef  int /*<<< orphan*/  elf_fpregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int dump_task_fpu (struct task_struct *tsk, elf_fpregset_t *r)
{
	memcpy(r, tsk->thread.regs.fr, sizeof(*r));
	return 1;
}