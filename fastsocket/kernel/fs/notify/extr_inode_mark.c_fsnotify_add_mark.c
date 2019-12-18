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
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_fsnotify_mark_entries; } ;
struct fsnotify_mark_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  g_list; int /*<<< orphan*/  i_list; struct inode* inode; struct fsnotify_group* group; } ;
struct fsnotify_group {int /*<<< orphan*/  mark_lock; int /*<<< orphan*/  num_marks; int /*<<< orphan*/  mark_entries; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  __fsnotify_update_child_dentry_flags (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct fsnotify_mark_entry* fsnotify_find_mark_entry (struct fsnotify_group*,struct inode*) ; 
 int /*<<< orphan*/  fsnotify_get_mark (struct fsnotify_mark_entry*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark_entry*) ; 
 int /*<<< orphan*/  fsnotify_recalc_inode_mask_locked (struct inode*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct inode* igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int fsnotify_add_mark(struct fsnotify_mark_entry *entry,
		      struct fsnotify_group *group, struct inode *inode)
{
	struct fsnotify_mark_entry *lentry;
	int ret = 0;

	inode = igrab(inode);
	if (unlikely(!inode))
		return -EINVAL;

	/*
	 * LOCKING ORDER!!!!
	 * entry->lock
	 * group->mark_lock
	 * inode->i_lock
	 */
	spin_lock(&entry->lock);
	spin_lock(&group->mark_lock);
	spin_lock(&inode->i_lock);

	lentry = fsnotify_find_mark_entry(group, inode);
	if (!lentry) {
		entry->group = group;
		entry->inode = inode;

		hlist_add_head(&entry->i_list, &inode->i_fsnotify_mark_entries);
		list_add(&entry->g_list, &group->mark_entries);

		fsnotify_get_mark(entry); /* for i_list and g_list */

		atomic_inc(&group->num_marks);

		fsnotify_recalc_inode_mask_locked(inode);
	}

	spin_unlock(&inode->i_lock);
	spin_unlock(&group->mark_lock);
	spin_unlock(&entry->lock);

	if (lentry) {
		ret = -EEXIST;
		iput(inode);
		fsnotify_put_mark(lentry);
	} else {
		__fsnotify_update_child_dentry_flags(inode);
	}

	return ret;
}