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
struct lockdep_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_chain_key (struct task_struct*) ; 
 int /*<<< orphan*/  check_unlock (struct task_struct*,struct lockdep_map*,unsigned long) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  lock_release_nested (struct task_struct*,struct lockdep_map*,unsigned long) ; 
 int /*<<< orphan*/  lock_release_non_nested (struct task_struct*,struct lockdep_map*,unsigned long) ; 

__attribute__((used)) static void
__lock_release(struct lockdep_map *lock, int nested, unsigned long ip)
{
	struct task_struct *curr = current;

	if (!check_unlock(curr, lock, ip))
		return;

	if (nested) {
		if (!lock_release_nested(curr, lock, ip))
			return;
	} else {
		if (!lock_release_non_nested(curr, lock, ip))
			return;
	}

	check_chain_key(curr);
}