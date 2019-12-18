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
struct task_struct {int lockdep_depth; scalar_t__ held_locks; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_lock (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 

__attribute__((used)) static void lockdep_print_held_locks(struct task_struct *curr)
{
	int i, depth = curr->lockdep_depth;

	if (!depth) {
		printk("no locks held by %s/%d.\n", curr->comm, task_pid_nr(curr));
		return;
	}
	printk("%d lock%s held by %s/%d:\n",
		depth, depth > 1 ? "s" : "", curr->comm, task_pid_nr(curr));

	for (i = 0; i < depth; i++) {
		printk(" #%d: ", i);
		print_lock(curr->held_locks + i);
	}
}