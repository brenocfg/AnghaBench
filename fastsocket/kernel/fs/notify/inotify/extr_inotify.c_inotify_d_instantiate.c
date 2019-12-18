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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; scalar_t__ d_inode; struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_INOTIFY_PARENT_WATCHED ; 
 scalar_t__ inotify_inode_watched (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void inotify_d_instantiate(struct dentry *entry, struct inode *inode)
{
	struct dentry *parent;

	if (!inode)
		return;

	spin_lock(&entry->d_lock);
	parent = entry->d_parent;
	if (parent->d_inode && inotify_inode_watched(parent->d_inode))
		entry->d_flags |= DCACHE_INOTIFY_PARENT_WATCHED;
	spin_unlock(&entry->d_lock);
}