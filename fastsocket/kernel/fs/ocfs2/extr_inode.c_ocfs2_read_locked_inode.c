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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; int /*<<< orphan*/  fs_generation; } ;
struct ocfs2_find_inode_args {int fi_flags; scalar_t__ fi_blkno; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_rdev; } ;
struct TYPE_5__ {TYPE_1__ dev1; } ;
struct ocfs2_dinode {int i_flags; int /*<<< orphan*/  i_blkno; TYPE_2__ id1; int /*<<< orphan*/  i_mode; } ;
struct inode {int /*<<< orphan*/  i_rdev; struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip_open_lockres; int /*<<< orphan*/  ip_inode_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_BH_IGNORE_CACHE ; 
 int OCFS2_FI_FLAG_ORPHAN_RECOVERY ; 
 int OCFS2_FI_FLAG_SYSFILE ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_META ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_OPEN ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  OCFS2_SYSTEM_FL ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_decode_dev (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct ocfs2_find_inode_args*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_lock_res_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_mount_local (struct ocfs2_super*) ; 
 int ocfs2_open_lock (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_populate_inode (struct inode*,struct ocfs2_dinode*,int /*<<< orphan*/ ) ; 
 int ocfs2_read_blocks_sync (struct ocfs2_super*,scalar_t__,int,struct buffer_head**) ; 
 int ocfs2_read_inode_block_full (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int ocfs2_try_open_lock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_validate_inode_block (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_read_locked_inode(struct inode *inode,
				   struct ocfs2_find_inode_args *args)
{
	struct super_block *sb;
	struct ocfs2_super *osb;
	struct ocfs2_dinode *fe;
	struct buffer_head *bh = NULL;
	int status, can_lock;
	u32 generation = 0;

	mlog_entry("(0x%p, 0x%p)\n", inode, args);

	status = -EINVAL;
	if (inode == NULL || inode->i_sb == NULL) {
		mlog(ML_ERROR, "bad inode\n");
		return status;
	}
	sb = inode->i_sb;
	osb = OCFS2_SB(sb);

	if (!args) {
		mlog(ML_ERROR, "bad inode args\n");
		make_bad_inode(inode);
		return status;
	}

	/*
	 * To improve performance of cold-cache inode stats, we take
	 * the cluster lock here if possible.
	 *
	 * Generally, OCFS2 never trusts the contents of an inode
	 * unless it's holding a cluster lock, so taking it here isn't
	 * a correctness issue as much as it is a performance
	 * improvement.
	 *
	 * There are three times when taking the lock is not a good idea:
	 *
	 * 1) During startup, before we have initialized the DLM.
	 *
	 * 2) If we are reading certain system files which never get
	 *    cluster locks (local alloc, truncate log).
	 *
	 * 3) If the process doing the iget() is responsible for
	 *    orphan dir recovery. We're holding the orphan dir lock and
	 *    can get into a deadlock with another process on another
	 *    node in ->delete_inode().
	 *
	 * #1 and #2 can be simply solved by never taking the lock
	 * here for system files (which are the only type we read
	 * during mount). It's a heavier approach, but our main
	 * concern is user-accesible files anyway.
	 *
	 * #3 works itself out because we'll eventually take the
	 * cluster lock before trusting anything anyway.
	 */
	can_lock = !(args->fi_flags & OCFS2_FI_FLAG_SYSFILE)
		&& !(args->fi_flags & OCFS2_FI_FLAG_ORPHAN_RECOVERY)
		&& !ocfs2_mount_local(osb);

	/*
	 * To maintain backwards compatibility with older versions of
	 * ocfs2-tools, we still store the generation value for system
	 * files. The only ones that actually matter to userspace are
	 * the journals, but it's easier and inexpensive to just flag
	 * all system files similarly.
	 */
	if (args->fi_flags & OCFS2_FI_FLAG_SYSFILE)
		generation = osb->fs_generation;

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_inode_lockres,
				  OCFS2_LOCK_TYPE_META,
				  generation, inode);

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_open_lockres,
				  OCFS2_LOCK_TYPE_OPEN,
				  0, inode);

	if (can_lock) {
		status = ocfs2_open_lock(inode);
		if (status) {
			make_bad_inode(inode);
			mlog_errno(status);
			return status;
		}
		status = ocfs2_inode_lock(inode, NULL, 0);
		if (status) {
			make_bad_inode(inode);
			mlog_errno(status);
			return status;
		}
	}

	if (args->fi_flags & OCFS2_FI_FLAG_ORPHAN_RECOVERY) {
		status = ocfs2_try_open_lock(inode, 0);
		if (status) {
			make_bad_inode(inode);	
			return status;
		}
	}

	if (can_lock) {
		status = ocfs2_read_inode_block_full(inode, &bh,
						     OCFS2_BH_IGNORE_CACHE);
	} else {
		status = ocfs2_read_blocks_sync(osb, args->fi_blkno, 1, &bh);
		if (!status)
			status = ocfs2_validate_inode_block(osb->sb, bh);
	}
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = -EINVAL;
	fe = (struct ocfs2_dinode *) bh->b_data;

	/*
	 * This is a code bug. Right now the caller needs to
	 * understand whether it is asking for a system file inode or
	 * not so the proper lock names can be built.
	 */
	mlog_bug_on_msg(!!(fe->i_flags & cpu_to_le32(OCFS2_SYSTEM_FL)) !=
			!!(args->fi_flags & OCFS2_FI_FLAG_SYSFILE),
			"Inode %llu: system file state is ambigous\n",
			(unsigned long long)args->fi_blkno);

	if (S_ISCHR(le16_to_cpu(fe->i_mode)) ||
	    S_ISBLK(le16_to_cpu(fe->i_mode)))
		inode->i_rdev = huge_decode_dev(le64_to_cpu(fe->id1.dev1.i_rdev));

	ocfs2_populate_inode(inode, fe, 0);

	BUG_ON(args->fi_blkno != le64_to_cpu(fe->i_blkno));

	status = 0;

bail:
	if (can_lock)
		ocfs2_inode_unlock(inode, 0);

	if (status < 0)
		make_bad_inode(inode);

	if (args && bh)
		brelse(bh);

	mlog_exit(status);
	return status;
}