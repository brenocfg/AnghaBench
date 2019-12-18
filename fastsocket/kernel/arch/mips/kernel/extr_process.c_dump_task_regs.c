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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  elf_gregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  elf_dump_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 

int dump_task_regs(struct task_struct *tsk, elf_gregset_t *regs)
{
	elf_dump_regs(*regs, task_pt_regs(tsk));
	return 1;
}