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
struct fsnotify_group {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fsnotify_evict_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  atomic_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_destroy_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_grp_mutex ; 
 int /*<<< orphan*/  fsnotify_grp_srcu ; 
 int /*<<< orphan*/  fsnotify_recalc_global_mask () ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void fsnotify_put_group(struct fsnotify_group *group)
{
	if (!atomic_dec_and_mutex_lock(&group->refcnt, &fsnotify_grp_mutex))
		return;

	/*
	 * OK, now we know that there's no other users *and* we hold mutex,
	 * so no new references will appear
	 */
	__fsnotify_evict_group(group);

	/*
	 * now it's off the list, so the only thing we might care about is
	 * srcu access....
	 */
	mutex_unlock(&fsnotify_grp_mutex);
	synchronize_srcu(&fsnotify_grp_srcu);

	/* and now it is really dead. _Nothing_ could be seeing it */
	fsnotify_recalc_global_mask();
	fsnotify_destroy_group(group);
}