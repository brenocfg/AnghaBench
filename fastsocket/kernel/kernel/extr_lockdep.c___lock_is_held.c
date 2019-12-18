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
struct task_struct {int lockdep_depth; struct held_lock* held_locks; } ;
struct lockdep_map {int dummy; } ;
struct held_lock {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 scalar_t__ match_held_lock (struct held_lock*,struct lockdep_map*) ; 

__attribute__((used)) static int __lock_is_held(struct lockdep_map *lock)
{
	struct task_struct *curr = current;
	int i;

	for (i = 0; i < curr->lockdep_depth; i++) {
		struct held_lock *hlock = curr->held_locks + i;

		if (match_held_lock(hlock, lock))
			return 1;
	}

	return 0;
}