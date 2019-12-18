#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inotify_watch {int wd; TYPE_1__* inode; int /*<<< orphan*/  i_list; int /*<<< orphan*/  h_list; struct inotify_handle* ih; int /*<<< orphan*/  mask; } ;
struct inotify_handle {int /*<<< orphan*/  mutex; int /*<<< orphan*/  watches; } ;
typedef  int s32 ;
struct TYPE_3__ {int /*<<< orphan*/  inotify_watches; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_inotify_handle (struct inotify_handle*) ; 
 TYPE_1__* igrab (TYPE_1__*) ; 
 int inotify_handle_get_wd (struct inotify_handle*,struct inotify_watch*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

s32 inotify_clone_watch(struct inotify_watch *old, struct inotify_watch *new)
{
	struct inotify_handle *ih = old->ih;
	int ret = 0;

	new->mask = old->mask;
	new->ih = ih;

	mutex_lock(&ih->mutex);

	/* Initialize a new watch */
	ret = inotify_handle_get_wd(ih, new);
	if (unlikely(ret))
		goto out;
	ret = new->wd;

	get_inotify_handle(ih);

	new->inode = igrab(old->inode);

	list_add(&new->h_list, &ih->watches);
	list_add(&new->i_list, &old->inode->inotify_watches);
out:
	mutex_unlock(&ih->mutex);
	return ret;
}