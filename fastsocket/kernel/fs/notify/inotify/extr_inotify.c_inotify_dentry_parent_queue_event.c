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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; struct inode* d_inode; struct dentry* d_parent; } ;

/* Variables and functions */
 int DCACHE_INOTIFY_PARENT_WATCHED ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inotify_inode_queue_event (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct inode*) ; 
 scalar_t__ inotify_inode_watched (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void inotify_dentry_parent_queue_event(struct dentry *dentry, u32 mask,
				       u32 cookie, const char *name)
{
	struct dentry *parent;
	struct inode *inode;

	if (!(dentry->d_flags & DCACHE_INOTIFY_PARENT_WATCHED))
		return;

	spin_lock(&dentry->d_lock);
	parent = dentry->d_parent;
	inode = parent->d_inode;

	if (inotify_inode_watched(inode)) {
		dget(parent);
		spin_unlock(&dentry->d_lock);
		inotify_inode_queue_event(inode, mask, cookie, name,
					  dentry->d_inode);
		dput(parent);
	} else
		spin_unlock(&dentry->d_lock);
}