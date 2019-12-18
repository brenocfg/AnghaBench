#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_lock; } ;
struct fsnotify_mark_entry {int /*<<< orphan*/  lock; struct fsnotify_group* group; int /*<<< orphan*/  g_list; struct inode* inode; int /*<<< orphan*/  i_list; int /*<<< orphan*/  refcnt; } ;
struct fsnotify_group {int /*<<< orphan*/  num_marks; TYPE_1__* ops; int /*<<< orphan*/  mark_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* freeing_mark ) (struct fsnotify_mark_entry*,struct fsnotify_group*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_final_destroy_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark_entry*) ; 
 int /*<<< orphan*/  fsnotify_recalc_inode_mask_locked (struct inode*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fsnotify_mark_entry*,struct fsnotify_group*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void fsnotify_destroy_mark_by_entry(struct fsnotify_mark_entry *entry)
{
	struct fsnotify_group *group;
	struct inode *inode;

	spin_lock(&entry->lock);

	group = entry->group;
	inode = entry->inode;

	BUG_ON(group && !inode);
	BUG_ON(!group && inode);

	/* if !group something else already marked this to die */
	if (!group) {
		spin_unlock(&entry->lock);
		return;
	}

	/* 1 from caller and 1 for being on i_list/g_list */
	BUG_ON(atomic_read(&entry->refcnt) < 2);

	spin_lock(&group->mark_lock);
	spin_lock(&inode->i_lock);

	hlist_del_init(&entry->i_list);
	entry->inode = NULL;

	list_del_init(&entry->g_list);
	entry->group = NULL;

	fsnotify_put_mark(entry); /* for i_list and g_list */

	/*
	 * this mark is now off the inode->i_fsnotify_mark_entries list and we
	 * hold the inode->i_lock, so this is the perfect time to update the
	 * inode->i_fsnotify_mask
	 */
	fsnotify_recalc_inode_mask_locked(inode);

	spin_unlock(&inode->i_lock);
	spin_unlock(&group->mark_lock);
	spin_unlock(&entry->lock);

	/*
	 * Some groups like to know that marks are being freed.  This is a
	 * callback to the group function to let it know that this entry
	 * is being freed.
	 */
	if (group->ops->freeing_mark)
		group->ops->freeing_mark(entry, group);

	/*
	 * __fsnotify_update_child_dentry_flags(inode);
	 *
	 * I really want to call that, but we can't, we have no idea if the inode
	 * still exists the second we drop the entry->lock.
	 *
	 * The next time an event arrive to this inode from one of it's children
	 * __fsnotify_parent will see that the inode doesn't care about it's
	 * children and will update all of these flags then.  So really this
	 * is just a lazy update (and could be a perf win...)
	 */


	iput(inode);

	/*
	 * it's possible that this group tried to destroy itself, but this
	 * this mark was simultaneously being freed by inode.  If that's the
	 * case, we finish freeing the group here.
	 */
	if (unlikely(atomic_dec_and_test(&group->num_marks)))
		fsnotify_final_destroy_group(group);
}