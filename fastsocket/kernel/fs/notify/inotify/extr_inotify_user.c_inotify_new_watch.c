#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int mask; } ;
struct inotify_inode_mark_entry {int wd; TYPE_3__ fsn_entry; } ;
struct inode {int dummy; } ;
struct TYPE_9__ {int last_wd; TYPE_1__* user; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct fsnotify_group {int mask; TYPE_2__ inotify_data; } ;
typedef  int __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  inotify_watches; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int fsnotify_add_mark (TYPE_3__*,struct fsnotify_group*,struct inode*) ; 
 int /*<<< orphan*/  fsnotify_get_mark (TYPE_3__*) ; 
 int /*<<< orphan*/  fsnotify_init_mark (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_put_mark (TYPE_3__*) ; 
 int /*<<< orphan*/  fsnotify_recalc_group_mask (struct fsnotify_group*) ; 
 int idr_get_new_above (int /*<<< orphan*/ *,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int inotify_arg_to_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_free_mark ; 
 int /*<<< orphan*/  inotify_inode_mark_cachep ; 
 scalar_t__ inotify_max_user_watches ; 
 int /*<<< orphan*/  inotify_remove_from_idr (struct fsnotify_group*,struct inotify_inode_mark_entry*) ; 
 struct inotify_inode_mark_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct inotify_inode_mark_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int inotify_new_watch(struct fsnotify_group *group,
			     struct inode *inode,
			     u32 arg)
{
	struct inotify_inode_mark_entry *tmp_ientry;
	__u32 mask;
	int ret;

	/* don't allow invalid bits: we don't want flags set */
	mask = inotify_arg_to_mask(arg);
	if (unlikely(!mask))
		return -EINVAL;

	tmp_ientry = kmem_cache_alloc(inotify_inode_mark_cachep, GFP_KERNEL);
	if (unlikely(!tmp_ientry))
		return -ENOMEM;

	fsnotify_init_mark(&tmp_ientry->fsn_entry, inotify_free_mark);
	tmp_ientry->fsn_entry.mask = mask;
	tmp_ientry->wd = -1;

	ret = -ENOSPC;
	if (atomic_read(&group->inotify_data.user->inotify_watches) >= inotify_max_user_watches)
		goto out_err;
retry:
	ret = -ENOMEM;
	if (unlikely(!idr_pre_get(&group->inotify_data.idr, GFP_KERNEL)))
		goto out_err;

	/* we are putting the mark on the idr, take a reference */
	fsnotify_get_mark(&tmp_ientry->fsn_entry);

	spin_lock(&group->inotify_data.idr_lock);
	ret = idr_get_new_above(&group->inotify_data.idr, &tmp_ientry->fsn_entry,
				group->inotify_data.last_wd +  1,
				&tmp_ientry->wd);
	spin_unlock(&group->inotify_data.idr_lock);
	if (ret) {
		/* we didn't get on the idr, drop the idr reference */
		fsnotify_put_mark(&tmp_ientry->fsn_entry);

		/* idr was out of memory allocate and try again */
		if (ret == -EAGAIN)
			goto retry;
		goto out_err;
	}

	/* we are on the idr, now get on the inode */
	ret = fsnotify_add_mark(&tmp_ientry->fsn_entry, group, inode);
	if (ret) {
		/* we failed to get on the inode, get off the idr */
		inotify_remove_from_idr(group, tmp_ientry);
		goto out_err;
	}

	/* update the idr hint, who cares about races, it's just a hint */
	group->inotify_data.last_wd = tmp_ientry->wd;

	/* increment the number of watches the user has */
	atomic_inc(&group->inotify_data.user->inotify_watches);

	/* return the watch descriptor for this new entry */
	ret = tmp_ientry->wd;

	/* match the ref from fsnotify_init_markentry() */
	fsnotify_put_mark(&tmp_ientry->fsn_entry);

	/* if this mark added a new event update the group mask */
	if (mask & ~group->mask)
		fsnotify_recalc_group_mask(group);

out_err:
	if (ret < 0)
		kmem_cache_free(inotify_inode_mark_cachep, tmp_ientry);

	return ret;
}