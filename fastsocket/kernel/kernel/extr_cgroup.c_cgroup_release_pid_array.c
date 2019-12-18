#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ns; } ;
struct cgroup_pidlist {int /*<<< orphan*/  mutex; TYPE_2__* owner; TYPE_1__ key; int /*<<< orphan*/  list; int /*<<< orphan*/  links; int /*<<< orphan*/  use_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  pidlist_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cgroup_pidlist*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_release_pid_array(struct cgroup_pidlist *l)
{
	/*
	 * the case where we're the last user of this particular pidlist will
	 * have us remove it from the cgroup's list, which entails taking the
	 * mutex. since in pidlist_find the pidlist->lock depends on cgroup->
	 * pidlist_mutex, we have to take pidlist_mutex first.
	 */
	mutex_lock(&l->owner->pidlist_mutex);
	down_write(&l->mutex);
	BUG_ON(!l->use_count);
	if (!--l->use_count) {
		/* we're the last user if refcount is 0; remove and free */
		list_del(&l->links);
		mutex_unlock(&l->owner->pidlist_mutex);
		pidlist_free(l->list);
		put_pid_ns(l->key.ns);
		up_write(&l->mutex);
		kfree(l);
		return;
	}
	mutex_unlock(&l->owner->pidlist_mutex);
	up_write(&l->mutex);
}