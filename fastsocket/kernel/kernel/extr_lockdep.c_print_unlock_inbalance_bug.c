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
struct lockdep_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_locks_off () ; 
 scalar_t__ debug_locks_silent ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  lockdep_print_held_locks (struct task_struct*) ; 
 int /*<<< orphan*/  print_ip_sym (unsigned long) ; 
 int /*<<< orphan*/  print_lockdep_cache (struct lockdep_map*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 

__attribute__((used)) static int
print_unlock_inbalance_bug(struct task_struct *curr, struct lockdep_map *lock,
			   unsigned long ip)
{
	if (!debug_locks_off())
		return 0;
	if (debug_locks_silent)
		return 0;

	printk("\n=====================================\n");
	printk(  "[ BUG: bad unlock balance detected! ]\n");
	printk(  "-------------------------------------\n");
	printk("%s/%d is trying to release lock (",
		curr->comm, task_pid_nr(curr));
	print_lockdep_cache(lock);
	printk(") at:\n");
	print_ip_sym(ip);
	printk("but there are no more locks to release!\n");
	printk("\nother info that might help us debug this:\n");
	lockdep_print_held_locks(curr);

	printk("\nstack backtrace:\n");
	dump_stack();

	return 0;
}