#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_2__* dq_op; int /*<<< orphan*/  s_bdev; TYPE_1__* s_op; } ;
struct quota_info {int flags; int /*<<< orphan*/  dqonoff_mutex; int /*<<< orphan*/  dqptr_sem; int /*<<< orphan*/ ** files; int /*<<< orphan*/  dqio_mutex; TYPE_4__** ops; TYPE_3__* info; } ;
struct quota_format_type {TYPE_4__* qf_ops; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct TYPE_8__ {int (* read_file_info ) (struct super_block*,int) ;int /*<<< orphan*/  (* check_quota_file ) (struct super_block*,int) ;} ;
struct TYPE_7__ {int dqi_fmt_id; int /*<<< orphan*/  dqi_dirty_list; struct quota_format_type* dqi_format; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* drop ) (struct inode*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  quota_read; int /*<<< orphan*/  quota_write; } ;

/* Variables and functions */
 int DQUOT_QUOTA_SYS_FILE ; 
 unsigned int DQUOT_USAGE_ENABLED ; 
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EROFS ; 
 int ESRCH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_RDONLY (struct inode*) ; 
 int /*<<< orphan*/  I_MUTEX_QUOTA ; 
 int S_IMMUTABLE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int S_NOATIME ; 
 int S_NOQUOTA ; 
 int /*<<< orphan*/  add_dquot_ref (struct super_block*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_state_lock ; 
 int dquot_state_flag (unsigned int,int) ; 
 struct quota_format_type* find_quota_format (int) ; 
 int /*<<< orphan*/ * igrab (struct inode*) ; 
 int /*<<< orphan*/  invalidate_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_quota_format (struct quota_format_type*) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 scalar_t__ sb_has_quota_loaded (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 
 int /*<<< orphan*/  stub2 (struct super_block*,int) ; 
 int stub3 (struct super_block*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

__attribute__((used)) static int vfs_load_quota_inode(struct inode *inode, int type, int format_id,
	unsigned int flags)
{
	struct quota_format_type *fmt = find_quota_format(format_id);
	struct super_block *sb = inode->i_sb;
	struct quota_info *dqopt = sb_dqopt(sb);
	int error;
	int oldflags = -1;

	if (!fmt)
		return -ESRCH;
	if (!S_ISREG(inode->i_mode)) {
		error = -EACCES;
		goto out_fmt;
	}
	if (IS_RDONLY(inode)) {
		error = -EROFS;
		goto out_fmt;
	}
	if (!sb->s_op->quota_write || !sb->s_op->quota_read) {
		error = -EINVAL;
		goto out_fmt;
	}
	/* Usage always has to be set... */
	if (!(flags & DQUOT_USAGE_ENABLED)) {
		error = -EINVAL;
		goto out_fmt;
	}

	if (!(dqopt->flags & DQUOT_QUOTA_SYS_FILE)) {
		/* As we bypass the pagecache we must now flush the inode so
		 * that we see all the changes from userspace... */
		write_inode_now(inode, 1);
		/* And now flush the block cache so that kernel sees the
		 * changes */
		invalidate_bdev(sb->s_bdev);
	}
	mutex_lock(&dqopt->dqonoff_mutex);
	if (sb_has_quota_loaded(sb, type)) {
		error = -EBUSY;
		goto out_lock;
	}

	if (!(dqopt->flags & DQUOT_QUOTA_SYS_FILE)) {
		/* We don't want quota and atime on quota files (deadlocks
		 * possible) Also nobody should write to the file - we use
		 * special IO operations which ignore the immutable bit. */
		down_write(&dqopt->dqptr_sem);
		mutex_lock_nested(&inode->i_mutex, I_MUTEX_QUOTA);
		oldflags = inode->i_flags & (S_NOATIME | S_IMMUTABLE |
					     S_NOQUOTA);
		inode->i_flags |= S_NOQUOTA | S_NOATIME | S_IMMUTABLE;
		mutex_unlock(&inode->i_mutex);
		up_write(&dqopt->dqptr_sem);
		sb->dq_op->drop(inode);
	}

	error = -EIO;
	dqopt->files[type] = igrab(inode);
	if (!dqopt->files[type])
		goto out_lock;
	error = -EINVAL;
	if (!fmt->qf_ops->check_quota_file(sb, type))
		goto out_file_init;

	dqopt->ops[type] = fmt->qf_ops;
	dqopt->info[type].dqi_format = fmt;
	dqopt->info[type].dqi_fmt_id = format_id;
	INIT_LIST_HEAD(&dqopt->info[type].dqi_dirty_list);
	mutex_lock(&dqopt->dqio_mutex);
	error = dqopt->ops[type]->read_file_info(sb, type);
	if (error < 0) {
		mutex_unlock(&dqopt->dqio_mutex);
		goto out_file_init;
	}
	mutex_unlock(&dqopt->dqio_mutex);
	spin_lock(&dq_state_lock);
	dqopt->flags |= dquot_state_flag(flags, type);
	spin_unlock(&dq_state_lock);

	add_dquot_ref(sb, type);
	mutex_unlock(&dqopt->dqonoff_mutex);

	return 0;

out_file_init:
	dqopt->files[type] = NULL;
	iput(inode);
out_lock:
	if (oldflags != -1) {
		down_write(&dqopt->dqptr_sem);
		mutex_lock_nested(&inode->i_mutex, I_MUTEX_QUOTA);
		/* Set the flags back (in the case of accidental quotaon()
		 * on a wrong file we don't want to mess up the flags) */
		inode->i_flags &= ~(S_NOATIME | S_NOQUOTA | S_IMMUTABLE);
		inode->i_flags |= oldflags;
		mutex_unlock(&inode->i_mutex);
		up_write(&dqopt->dqptr_sem);
	}
	mutex_unlock(&dqopt->dqonoff_mutex);
out_fmt:
	put_quota_format(fmt);

	return error; 
}