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
struct switch_stack {int /*<<< orphan*/  fp; } ;
typedef  int /*<<< orphan*/  elf_fpreg_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ task_pt_regs (struct task_struct*) ; 

int
dump_elf_task_fp(elf_fpreg_t *dest, struct task_struct *task)
{
	struct switch_stack *sw = (struct switch_stack *)task_pt_regs(task) - 1;
	memcpy(dest, sw->fp, 32 * 8);
	return 1;
}