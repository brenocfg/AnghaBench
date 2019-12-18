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
struct task_struct {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_locks_off () ; 
 scalar_t__ debug_locks_silent ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  lockdep_print_held_locks (struct task_struct*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 

__attribute__((used)) static void print_held_locks_bug(struct task_struct *curr)
{
	if (!debug_locks_off())
		return;
	if (debug_locks_silent)
		return;

	printk("\n=====================================\n");
	printk(  "[ BUG: lock held at task exit time! ]\n");
	printk(  "-------------------------------------\n");
	printk("%s/%d is exiting with locks still held!\n",
		curr->comm, task_pid_nr(curr));
	lockdep_print_held_locks(curr);

	printk("\nstack backtrace:\n");
	dump_stack();
}