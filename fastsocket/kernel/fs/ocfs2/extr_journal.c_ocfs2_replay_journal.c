#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ocfs2_super {scalar_t__* slot_recovery_generations; TYPE_3__* sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  ij_flags; } ;
struct TYPE_7__ {TYPE_1__ journal1; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_check; TYPE_2__ id1; int /*<<< orphan*/  i_clusters; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_9__ {void* ip_clusters; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EBUSY ; 
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 TYPE_5__* OCFS2_I (struct inode*) ; 
 unsigned int OCFS2_JOURNAL_DIRTY_FL ; 
 int /*<<< orphan*/  OCFS2_META_LOCK_RECOVERY ; 
 int /*<<< orphan*/  REPLAY_NEEDED ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy (int /*<<< orphan*/ *) ; 
 int jbd2_journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jbd2_journal_init_inode (struct inode*) ; 
 int jbd2_journal_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ *) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_bump_recovery_generation (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_clear_journal_error (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_compute_meta_ecc (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int ocfs2_force_read_journal (struct inode*) ; 
 scalar_t__ ocfs2_get_recovery_generation (struct ocfs2_dinode*) ; 
 int ocfs2_inode_lock_full (struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_read_journal_inode (struct ocfs2_super*,int,struct buffer_head**,struct inode**) ; 
 int /*<<< orphan*/  ocfs2_replay_map_set_state (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_write_block (struct ocfs2_super*,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_replay_journal(struct ocfs2_super *osb,
				int node_num,
				int slot_num)
{
	int status;
	int got_lock = 0;
	unsigned int flags;
	struct inode *inode = NULL;
	struct ocfs2_dinode *fe;
	journal_t *journal = NULL;
	struct buffer_head *bh = NULL;
	u32 slot_reco_gen;

	status = ocfs2_read_journal_inode(osb, slot_num, &bh, &inode);
	if (status) {
		mlog_errno(status);
		goto done;
	}

	fe = (struct ocfs2_dinode *)bh->b_data;
	slot_reco_gen = ocfs2_get_recovery_generation(fe);
	brelse(bh);
	bh = NULL;

	/*
	 * As the fs recovery is asynchronous, there is a small chance that
	 * another node mounted (and recovered) the slot before the recovery
	 * thread could get the lock. To handle that, we dirty read the journal
	 * inode for that slot to get the recovery generation. If it is
	 * different than what we expected, the slot has been recovered.
	 * If not, it needs recovery.
	 */
	if (osb->slot_recovery_generations[slot_num] != slot_reco_gen) {
		mlog(0, "Slot %u already recovered (old/new=%u/%u)\n", slot_num,
		     osb->slot_recovery_generations[slot_num], slot_reco_gen);
		osb->slot_recovery_generations[slot_num] = slot_reco_gen;
		status = -EBUSY;
		goto done;
	}

	/* Continue with recovery as the journal has not yet been recovered */

	status = ocfs2_inode_lock_full(inode, &bh, 1, OCFS2_META_LOCK_RECOVERY);
	if (status < 0) {
		mlog(0, "status returned from ocfs2_inode_lock=%d\n", status);
		if (status != -ERESTARTSYS)
			mlog(ML_ERROR, "Could not lock journal!\n");
		goto done;
	}
	got_lock = 1;

	fe = (struct ocfs2_dinode *) bh->b_data;

	flags = le32_to_cpu(fe->id1.journal1.ij_flags);
	slot_reco_gen = ocfs2_get_recovery_generation(fe);

	if (!(flags & OCFS2_JOURNAL_DIRTY_FL)) {
		mlog(0, "No recovery required for node %d\n", node_num);
		/* Refresh recovery generation for the slot */
		osb->slot_recovery_generations[slot_num] = slot_reco_gen;
		goto done;
	}

	/* we need to run complete recovery for offline orphan slots */
	ocfs2_replay_map_set_state(osb, REPLAY_NEEDED);

	mlog(ML_NOTICE, "Recovering node %d from slot %d on device (%u,%u)\n",
	     node_num, slot_num,
	     MAJOR(osb->sb->s_dev), MINOR(osb->sb->s_dev));

	OCFS2_I(inode)->ip_clusters = le32_to_cpu(fe->i_clusters);

	status = ocfs2_force_read_journal(inode);
	if (status < 0) {
		mlog_errno(status);
		goto done;
	}

	mlog(0, "calling journal_init_inode\n");
	journal = jbd2_journal_init_inode(inode);
	if (journal == NULL) {
		mlog(ML_ERROR, "Linux journal layer error\n");
		status = -EIO;
		goto done;
	}

	status = jbd2_journal_load(journal);
	if (status < 0) {
		mlog_errno(status);
		if (!igrab(inode))
			BUG();
		jbd2_journal_destroy(journal);
		goto done;
	}

	ocfs2_clear_journal_error(osb->sb, journal, slot_num);

	/* wipe the journal */
	mlog(0, "flushing the journal.\n");
	jbd2_journal_lock_updates(journal);
	status = jbd2_journal_flush(journal);
	jbd2_journal_unlock_updates(journal);
	if (status < 0)
		mlog_errno(status);

	/* This will mark the node clean */
	flags = le32_to_cpu(fe->id1.journal1.ij_flags);
	flags &= ~OCFS2_JOURNAL_DIRTY_FL;
	fe->id1.journal1.ij_flags = cpu_to_le32(flags);

	/* Increment recovery generation to indicate successful recovery */
	ocfs2_bump_recovery_generation(fe);
	osb->slot_recovery_generations[slot_num] =
					ocfs2_get_recovery_generation(fe);

	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &fe->i_check);
	status = ocfs2_write_block(osb, bh, INODE_CACHE(inode));
	if (status < 0)
		mlog_errno(status);

	if (!igrab(inode))
		BUG();

	jbd2_journal_destroy(journal);

done:
	/* drop the lock on this nodes journal */
	if (got_lock)
		ocfs2_inode_unlock(inode, 1);

	if (inode)
		iput(inode);

	brelse(bh);

	mlog_exit(status);
	return status;
}