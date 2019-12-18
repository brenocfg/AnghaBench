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
typedef  int u32 ;
struct inotify_watch {int mask; int wd; int /*<<< orphan*/  i_list; int /*<<< orphan*/  h_list; int /*<<< orphan*/  inode; struct inotify_handle* ih; } ;
struct inotify_handle {int /*<<< orphan*/  mutex; int /*<<< orphan*/  watches; } ;
struct inode {int /*<<< orphan*/  inotify_mutex; int /*<<< orphan*/  inotify_watches; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int IN_ALL_EVENTS ; 
 int IN_ONESHOT ; 
 int /*<<< orphan*/  get_inotify_handle (struct inotify_handle*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int inotify_handle_get_wd (struct inotify_handle*,struct inotify_watch*) ; 
 int /*<<< orphan*/  inotify_inode_watched (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dentry_child_flags (struct inode*,int) ; 
 scalar_t__ unlikely (int) ; 

s32 inotify_add_watch(struct inotify_handle *ih, struct inotify_watch *watch,
		      struct inode *inode, u32 mask)
{
	int ret = 0;
	int newly_watched;

	/* don't allow invalid bits: we don't want flags set */
	mask &= IN_ALL_EVENTS | IN_ONESHOT;
	if (unlikely(!mask))
		return -EINVAL;
	watch->mask = mask;

	mutex_lock(&inode->inotify_mutex);
	mutex_lock(&ih->mutex);

	/* Initialize a new watch */
	ret = inotify_handle_get_wd(ih, watch);
	if (unlikely(ret))
		goto out;
	ret = watch->wd;

	/* save a reference to handle and bump the count to make it official */
	get_inotify_handle(ih);
	watch->ih = ih;

	/*
	 * Save a reference to the inode and bump the ref count to make it
	 * official.  We hold a reference to nameidata, which makes this safe.
	 */
	watch->inode = igrab(inode);

	/* Add the watch to the handle's and the inode's list */
	newly_watched = !inotify_inode_watched(inode);
	list_add(&watch->h_list, &ih->watches);
	list_add(&watch->i_list, &inode->inotify_watches);
	/*
	 * Set child flags _after_ adding the watch, so there is no race
	 * windows where newly instantiated children could miss their parent's
	 * watched flag.
	 */
	if (newly_watched)
		set_dentry_child_flags(inode, 1);

out:
	mutex_unlock(&ih->mutex);
	mutex_unlock(&inode->inotify_mutex);
	return ret;
}