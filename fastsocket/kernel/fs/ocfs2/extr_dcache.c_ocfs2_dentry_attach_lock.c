#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_5__ {int /*<<< orphan*/  l_name; } ;
struct ocfs2_dentry_lock {scalar_t__ dl_parent_blkno; int dl_count; TYPE_2__ dl_lockres; int /*<<< orphan*/  dl_inode; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {struct ocfs2_dentry_lock* d_fsdata; TYPE_1__ d_name; } ;
struct TYPE_6__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  dentry_attach_lock ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dentry_lock*) ; 
 struct ocfs2_dentry_lock* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dentry_lock (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dentry_lock_res_init (struct ocfs2_dentry_lock*,scalar_t__,struct inode*) ; 
 int /*<<< orphan*/  ocfs2_dentry_unlock (struct dentry*,int /*<<< orphan*/ ) ; 
 struct dentry* ocfs2_find_local_alias (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_dentry_attach_lock(struct dentry *dentry,
			     struct inode *inode,
			     u64 parent_blkno)
{
	int ret;
	struct dentry *alias;
	struct ocfs2_dentry_lock *dl = dentry->d_fsdata;

	mlog(0, "Attach \"%.*s\", parent %llu, fsdata: %p\n",
	     dentry->d_name.len, dentry->d_name.name,
	     (unsigned long long)parent_blkno, dl);

	/*
	 * Negative dentry. We ignore these for now.
	 *
	 * XXX: Could we can improve ocfs2_dentry_revalidate() by
	 * tracking these?
	 */
	if (!inode)
		return 0;

	if (dl) {
		mlog_bug_on_msg(dl->dl_parent_blkno != parent_blkno,
				" \"%.*s\": old parent: %llu, new: %llu\n",
				dentry->d_name.len, dentry->d_name.name,
				(unsigned long long)parent_blkno,
				(unsigned long long)dl->dl_parent_blkno);
		return 0;
	}

	alias = ocfs2_find_local_alias(inode, parent_blkno, 0);
	if (alias) {
		/*
		 * Great, an alias exists, which means we must have a
		 * dentry lock already. We can just grab the lock off
		 * the alias and add it to the list.
		 *
		 * We're depending here on the fact that this dentry
		 * was found and exists in the dcache and so must have
		 * a reference to the dentry_lock because we can't
		 * race creates. Final dput() cannot happen on it
		 * since we have it pinned, so our reference is safe.
		 */
		dl = alias->d_fsdata;
		mlog_bug_on_msg(!dl, "parent %llu, ino %llu\n",
				(unsigned long long)parent_blkno,
				(unsigned long long)OCFS2_I(inode)->ip_blkno);

		mlog_bug_on_msg(dl->dl_parent_blkno != parent_blkno,
				" \"%.*s\": old parent: %llu, new: %llu\n",
				dentry->d_name.len, dentry->d_name.name,
				(unsigned long long)parent_blkno,
				(unsigned long long)dl->dl_parent_blkno);

		mlog(0, "Found: %s\n", dl->dl_lockres.l_name);

		goto out_attach;
	}

	/*
	 * There are no other aliases
	 */
	dl = kmalloc(sizeof(*dl), GFP_NOFS);
	if (!dl) {
		ret = -ENOMEM;
		mlog_errno(ret);
		return ret;
	}

	dl->dl_count = 0;
	/*
	 * Does this have to happen below, for all attaches, in case
	 * the struct inode gets blown away by the downconvert thread?
	 */
	dl->dl_inode = igrab(inode);
	dl->dl_parent_blkno = parent_blkno;
	ocfs2_dentry_lock_res_init(dl, parent_blkno, inode);

out_attach:
	spin_lock(&dentry_attach_lock);
	dentry->d_fsdata = dl;
	dl->dl_count++;
	spin_unlock(&dentry_attach_lock);

	/*
	 * This actually gets us our PRMODE level lock. From now on,
	 * we'll have a notification if one of these names is
	 * destroyed on another node.
	 */
	ret = ocfs2_dentry_lock(dentry, 0);
	if (!ret)
		ocfs2_dentry_unlock(dentry, 0);
	else
		mlog_errno(ret);

	/*
	 * In case of error, manually free the allocation and do the iput().
	 * We need to do this because error here means no d_instantiate(),
	 * which means iput() will not be called during dput(dentry).
	 */
	if (ret < 0 && !alias) {
		ocfs2_lock_res_free(&dl->dl_lockres);
		BUG_ON(dl->dl_count != 1);
		spin_lock(&dentry_attach_lock);
		dentry->d_fsdata = NULL;
		spin_unlock(&dentry_attach_lock);
		kfree(dl);
		iput(inode);
	}

	dput(alias);

	return ret;
}