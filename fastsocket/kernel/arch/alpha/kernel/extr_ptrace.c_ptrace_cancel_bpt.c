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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int bpt_nsaved; int /*<<< orphan*/ * bpt_insn; int /*<<< orphan*/ * bpt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  write_int (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ptrace_cancel_bpt(struct task_struct * child)
{
	int i, nsaved = task_thread_info(child)->bpt_nsaved;

	task_thread_info(child)->bpt_nsaved = 0;

	if (nsaved > 2) {
		printk("ptrace_cancel_bpt: bogus nsaved: %d!\n", nsaved);
		nsaved = 2;
	}

	for (i = 0; i < nsaved; ++i) {
		write_int(child, task_thread_info(child)->bpt_addr[i],
			  task_thread_info(child)->bpt_insn[i]);
	}
	return (nsaved != 0);
}