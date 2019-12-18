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
struct TYPE_3__ {TYPE_2__* user; int /*<<< orphan*/  idr; } ;
struct fsnotify_group {TYPE_1__ inotify_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  inotify_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (TYPE_2__*) ; 
 int /*<<< orphan*/  idr_callback ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsnotify_group*) ; 
 int /*<<< orphan*/  idr_remove_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inotify_free_group_priv(struct fsnotify_group *group)
{
	/* ideally the idr is empty and we won't hit the BUG in teh callback */
	idr_for_each(&group->inotify_data.idr, idr_callback, group);
	idr_remove_all(&group->inotify_data.idr);
	idr_destroy(&group->inotify_data.idr);
	atomic_dec(&group->inotify_data.user->inotify_devs);
	free_uid(group->inotify_data.user);
}