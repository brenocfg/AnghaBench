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
typedef  int /*<<< orphan*/  elf_greg_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_elf_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 

int
dump_elf_task(elf_greg_t *dest, struct task_struct *task)
{
	dump_elf_thread(dest, task_pt_regs(task), task_thread_info(task));
	return 1;
}