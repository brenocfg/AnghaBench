#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_inode_info {unsigned long long ip_blkno; int ip_flags; int /*<<< orphan*/  ip_jinode; scalar_t__ ip_dir_start_lookup; int /*<<< orphan*/  ip_open_count; int /*<<< orphan*/  ip_alloc_sem; int /*<<< orphan*/  ip_io_mutex; int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_open_lockres; int /*<<< orphan*/  ip_inode_lockres; int /*<<< orphan*/  ip_rw_lockres; int /*<<< orphan*/  ip_io_markers; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_7__ {TYPE_1__* journal; } ;
struct TYPE_6__ {int ci_flags; int /*<<< orphan*/  ci_num_cached; } ;
struct TYPE_5__ {int /*<<< orphan*/  j_journal; } ;

/* Variables and functions */
 TYPE_2__* INODE_CACHE (struct inode*) ; 
 int OCFS2_CACHE_FL_INLINE ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_DELETED ; 
 TYPE_3__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_release_jbd_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_checkpoint_inode (struct inode*) ; 
 int ocfs2_drop_inode_locks (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_extent_map_trunc (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_mark_lockres_freeing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  ocfs2_open_unlock (struct inode*) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ocfs2_clear_inode(struct inode *inode)
{
	int status;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	mlog_entry_void();

	if (!inode)
		goto bail;

	mlog(0, "Clearing inode: %llu, nlink = %u\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno, inode->i_nlink);

	mlog_bug_on_msg(OCFS2_SB(inode->i_sb) == NULL,
			"Inode=%lu\n", inode->i_ino);

	/* To preven remote deletes we hold open lock before, now it
	 * is time to unlock PR and EX open locks. */
	ocfs2_open_unlock(inode);

	/* Do these before all the other work so that we don't bounce
	 * the downconvert thread while waiting to destroy the locks. */
	ocfs2_mark_lockres_freeing(&oi->ip_rw_lockres);
	ocfs2_mark_lockres_freeing(&oi->ip_inode_lockres);
	ocfs2_mark_lockres_freeing(&oi->ip_open_lockres);

	/* We very well may get a clear_inode before all an inodes
	 * metadata has hit disk. Of course, we can't drop any cluster
	 * locks until the journal has finished with it. The only
	 * exception here are successfully wiped inodes - their
	 * metadata can now be considered to be part of the system
	 * inodes from which it came. */
	if (!(OCFS2_I(inode)->ip_flags & OCFS2_INODE_DELETED))
		ocfs2_checkpoint_inode(inode);

	mlog_bug_on_msg(!list_empty(&oi->ip_io_markers),
			"Clear inode of %llu, inode has io markers\n",
			(unsigned long long)oi->ip_blkno);

	ocfs2_extent_map_trunc(inode, 0);

	status = ocfs2_drop_inode_locks(inode);
	if (status < 0)
		mlog_errno(status);

	ocfs2_lock_res_free(&oi->ip_rw_lockres);
	ocfs2_lock_res_free(&oi->ip_inode_lockres);
	ocfs2_lock_res_free(&oi->ip_open_lockres);

	ocfs2_metadata_cache_exit(INODE_CACHE(inode));

	mlog_bug_on_msg(INODE_CACHE(inode)->ci_num_cached,
			"Clear inode of %llu, inode has %u cache items\n",
			(unsigned long long)oi->ip_blkno,
			INODE_CACHE(inode)->ci_num_cached);

	mlog_bug_on_msg(!(INODE_CACHE(inode)->ci_flags & OCFS2_CACHE_FL_INLINE),
			"Clear inode of %llu, inode has a bad flag\n",
			(unsigned long long)oi->ip_blkno);

	mlog_bug_on_msg(spin_is_locked(&oi->ip_lock),
			"Clear inode of %llu, inode is locked\n",
			(unsigned long long)oi->ip_blkno);

	mlog_bug_on_msg(!mutex_trylock(&oi->ip_io_mutex),
			"Clear inode of %llu, io_mutex is locked\n",
			(unsigned long long)oi->ip_blkno);
	mutex_unlock(&oi->ip_io_mutex);

	/*
	 * down_trylock() returns 0, down_write_trylock() returns 1
	 * kernel 1, world 0
	 */
	mlog_bug_on_msg(!down_write_trylock(&oi->ip_alloc_sem),
			"Clear inode of %llu, alloc_sem is locked\n",
			(unsigned long long)oi->ip_blkno);
	up_write(&oi->ip_alloc_sem);

	mlog_bug_on_msg(oi->ip_open_count,
			"Clear inode of %llu has open count %d\n",
			(unsigned long long)oi->ip_blkno, oi->ip_open_count);

	/* Clear all other flags. */
	oi->ip_flags = 0;
	oi->ip_dir_start_lookup = 0;
	oi->ip_blkno = 0ULL;

	/*
	 * ip_jinode is used to track txns against this inode. We ensure that
	 * the journal is flushed before journal shutdown. Thus it is safe to
	 * have inodes get cleaned up after journal shutdown.
	 */
	jbd2_journal_release_jbd_inode(OCFS2_SB(inode->i_sb)->journal->j_journal,
				       &oi->ip_jinode);

bail:
	mlog_exit_void();
}