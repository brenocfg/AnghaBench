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
struct lockdep_map {char* name; struct lock_class_key* key; int /*<<< orphan*/  cpu; int /*<<< orphan*/ * class_cache; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  debug_locks ; 
 int /*<<< orphan*/  printk (char*,struct lock_class_key*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  register_lock_class (struct lockdep_map*,int,int) ; 
 int /*<<< orphan*/  static_obj (struct lock_class_key*) ; 
 scalar_t__ unlikely (int) ; 

void lockdep_init_map(struct lockdep_map *lock, const char *name,
		      struct lock_class_key *key, int subclass)
{
	lock->class_cache = NULL;
#ifdef CONFIG_LOCK_STAT
	lock->cpu = raw_smp_processor_id();
#endif

	if (DEBUG_LOCKS_WARN_ON(!name)) {
		lock->name = "NULL";
		return;
	}

	lock->name = name;

	if (DEBUG_LOCKS_WARN_ON(!key))
		return;
	/*
	 * Sanity check, the lock-class key must be persistent:
	 */
	if (!static_obj(key)) {
		printk("BUG: key %p not in .data!\n", key);
		DEBUG_LOCKS_WARN_ON(1);
		return;
	}
	lock->key = key;

	if (unlikely(!debug_locks))
		return;

	if (subclass)
		register_lock_class(lock, subclass, 1);
}