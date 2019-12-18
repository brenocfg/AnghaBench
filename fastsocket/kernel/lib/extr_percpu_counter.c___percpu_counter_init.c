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
struct percpu_counter {int /*<<< orphan*/  list; int /*<<< orphan*/  counters; int /*<<< orphan*/  count; int /*<<< orphan*/  lock; } ;
struct lock_class_key {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  alloc_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 
 int /*<<< orphan*/  percpu_counters ; 
 int /*<<< orphan*/  percpu_counters_lock ; 
 int /*<<< orphan*/  s32 ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __percpu_counter_init(struct percpu_counter *fbc, s64 amount,
			  struct lock_class_key *key)
{
	spin_lock_init(&fbc->lock);
	lockdep_set_class(&fbc->lock, key);
	fbc->count = amount;
	fbc->counters = alloc_percpu(s32);
	if (!fbc->counters)
		return -ENOMEM;
#ifdef CONFIG_HOTPLUG_CPU
	spin_lock(&percpu_counters_lock);
	list_add(&fbc->list, &percpu_counters);
	spin_unlock(&percpu_counters_lock);
#endif
	return 0;
}