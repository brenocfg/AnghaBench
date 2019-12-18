#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int /*<<< orphan*/  sb; struct ocfs2_journal* journal; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_inode; struct buffer_head* j_bh; } ;
struct TYPE_3__ {int /*<<< orphan*/  ij_flags; } ;
struct TYPE_4__ {TYPE_1__ journal1; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_check; TYPE_2__ id1; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 unsigned int OCFS2_JOURNAL_DIRTY_FL ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_bump_recovery_generation (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_compute_meta_ecc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int ocfs2_write_block (struct ocfs2_super*,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_journal_toggle_dirty(struct ocfs2_super *osb,
				      int dirty, int replayed)
{
	int status;
	unsigned int flags;
	struct ocfs2_journal *journal = osb->journal;
	struct buffer_head *bh = journal->j_bh;
	struct ocfs2_dinode *fe;

	mlog_entry_void();

	fe = (struct ocfs2_dinode *)bh->b_data;

	/* The journal bh on the osb always comes from ocfs2_journal_init()
	 * and was validated there inside ocfs2_inode_lock_full().  It's a
	 * code bug if we mess it up. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	flags = le32_to_cpu(fe->id1.journal1.ij_flags);
	if (dirty)
		flags |= OCFS2_JOURNAL_DIRTY_FL;
	else
		flags &= ~OCFS2_JOURNAL_DIRTY_FL;
	fe->id1.journal1.ij_flags = cpu_to_le32(flags);

	if (replayed)
		ocfs2_bump_recovery_generation(fe);

	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &fe->i_check);
	status = ocfs2_write_block(osb, bh, INODE_CACHE(journal->j_inode));
	if (status < 0)
		mlog_errno(status);

	mlog_exit(status);
	return status;
}