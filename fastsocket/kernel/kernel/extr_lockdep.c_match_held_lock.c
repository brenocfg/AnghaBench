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
struct lockdep_map {struct lock_class* class_cache; } ;
struct lock_class {int dummy; } ;
struct held_lock {int class_idx; int /*<<< orphan*/  nest_lock; scalar_t__ references; struct lockdep_map* instance; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 struct lock_class* lock_classes ; 
 struct lock_class* look_up_lock_class (struct lockdep_map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_held_lock(struct held_lock *hlock, struct lockdep_map *lock)
{
	if (hlock->instance == lock)
		return 1;

	if (hlock->references) {
		struct lock_class *class = lock->class_cache;

		if (!class)
			class = look_up_lock_class(lock, 0);

		if (DEBUG_LOCKS_WARN_ON(!class))
			return 0;

		if (DEBUG_LOCKS_WARN_ON(!hlock->nest_lock))
			return 0;

		if (hlock->class_idx == class - lock_classes + 1)
			return 1;
	}

	return 0;
}