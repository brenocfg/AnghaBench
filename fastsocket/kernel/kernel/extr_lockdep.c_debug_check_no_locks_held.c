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
struct task_struct {scalar_t__ lockdep_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_held_locks_bug (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

void debug_check_no_locks_held(struct task_struct *task)
{
	if (unlikely(task->lockdep_depth > 0))
		print_held_locks_bug(task);
}