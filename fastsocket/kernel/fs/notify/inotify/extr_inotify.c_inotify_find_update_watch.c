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
struct inotify_watch {int mask; int wd; } ;
struct inotify_handle {int /*<<< orphan*/  mutex; } ;
struct inode {int /*<<< orphan*/  inotify_mutex; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int IN_ALL_EVENTS ; 
 int IN_MASK_ADD ; 
 int IN_ONESHOT ; 
 struct inotify_watch* inode_find_handle (struct inode*,struct inotify_handle*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

s32 inotify_find_update_watch(struct inotify_handle *ih, struct inode *inode,
			      u32 mask)
{
	struct inotify_watch *old;
	int mask_add = 0;
	int ret;

	if (mask & IN_MASK_ADD)
		mask_add = 1;

	/* don't allow invalid bits: we don't want flags set */
	mask &= IN_ALL_EVENTS | IN_ONESHOT;
	if (unlikely(!mask))
		return -EINVAL;

	mutex_lock(&inode->inotify_mutex);
	mutex_lock(&ih->mutex);

	/*
	 * Handle the case of re-adding a watch on an (inode,ih) pair that we
	 * are already watching.  We just update the mask and return its wd.
	 */
	old = inode_find_handle(inode, ih);
	if (unlikely(!old)) {
		ret = -ENOENT;
		goto out;
	}

	if (mask_add)
		old->mask |= mask;
	else
		old->mask = mask;
	ret = old->wd;
out:
	mutex_unlock(&ih->mutex);
	mutex_unlock(&inode->inotify_mutex);
	return ret;
}