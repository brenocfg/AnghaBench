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
struct inotify_watch {int wd; } ;
struct inotify_handle {int /*<<< orphan*/  mutex; } ;
struct inode {int /*<<< orphan*/  inotify_mutex; } ;
typedef  int s32 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  get_inotify_watch (struct inotify_watch*) ; 
 struct inotify_watch* inode_find_handle (struct inode*,struct inotify_handle*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct inotify_watch*) ; 

s32 inotify_find_watch(struct inotify_handle *ih, struct inode *inode,
		       struct inotify_watch **watchp)
{
	struct inotify_watch *old;
	int ret = -ENOENT;

	mutex_lock(&inode->inotify_mutex);
	mutex_lock(&ih->mutex);

	old = inode_find_handle(inode, ih);
	if (unlikely(old)) {
		get_inotify_watch(old); /* caller must put watch */
		*watchp = old;
		ret = old->wd;
	}

	mutex_unlock(&ih->mutex);
	mutex_unlock(&inode->inotify_mutex);

	return ret;
}