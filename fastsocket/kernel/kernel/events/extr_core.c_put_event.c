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
struct task_struct {int /*<<< orphan*/  perf_event_mutex; } ;
struct perf_event {int /*<<< orphan*/  owner_entry; int /*<<< orphan*/  owner; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 struct task_struct* ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_release_kernel (struct perf_event*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_read_barrier_depends () ; 

__attribute__((used)) static void put_event(struct perf_event *event)
{
	struct task_struct *owner;

	if (!atomic_long_dec_and_test(&event->refcount))
		return;

	rcu_read_lock();
	owner = ACCESS_ONCE(event->owner);
	/*
	 * Matches the smp_wmb() in perf_event_exit_task(). If we observe
	 * !owner it means the list deletion is complete and we can indeed
	 * free this event, otherwise we need to serialize on
	 * owner->perf_event_mutex.
	 */
	smp_read_barrier_depends();
	if (owner) {
		/*
		 * Since delayed_put_task_struct() also drops the last
		 * task reference we can safely take a new reference
		 * while holding the rcu_read_lock().
		 */
		get_task_struct(owner);
	}
	rcu_read_unlock();

	if (owner) {
		mutex_lock(&owner->perf_event_mutex);
		/*
		 * We have to re-check the event->owner field, if it is cleared
		 * we raced with perf_event_exit_task(), acquiring the mutex
		 * ensured they're done, and we can proceed with freeing the
		 * event.
		 */
		if (event->owner)
			list_del_init(&event->owner_entry);
		mutex_unlock(&owner->perf_event_mutex);
		put_task_struct(owner);
	}

	perf_event_release_kernel(event);
}