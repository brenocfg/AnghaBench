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
struct thread_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct reg_window32 {unsigned long* ins; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ current_thread_info () ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

void show_stack(struct task_struct *tsk, unsigned long *_ksp)
{
	unsigned long pc, fp;
	unsigned long task_base;
	struct reg_window32 *rw;
	int count = 0;

	if (tsk != NULL)
		task_base = (unsigned long) task_stack_page(tsk);
	else
		task_base = (unsigned long) current_thread_info();

	fp = (unsigned long) _ksp;
	do {
		/* Bogus frame pointer? */
		if (fp < (task_base + sizeof(struct thread_info)) ||
		    fp >= (task_base + (PAGE_SIZE << 1)))
			break;
		rw = (struct reg_window32 *) fp;
		pc = rw->ins[7];
		printk("[%08lx : ", pc);
		printk("%pS ] ", (void *) pc);
		fp = rw->ins[6];
	} while (++count < 16);
	printk("\n");
}