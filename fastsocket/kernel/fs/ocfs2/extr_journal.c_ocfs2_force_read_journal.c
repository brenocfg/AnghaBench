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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_size; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int CONCURRENT_JOURNAL_FILL ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (struct buffer_head**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_blocks_for_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int ocfs2_read_blocks_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_force_read_journal(struct inode *inode)
{
	int status = 0;
	int i;
	u64 v_blkno, p_blkno, p_blocks, num_blocks;
#define CONCURRENT_JOURNAL_FILL 32ULL
	struct buffer_head *bhs[CONCURRENT_JOURNAL_FILL];

	mlog_entry_void();

	memset(bhs, 0, sizeof(struct buffer_head *) * CONCURRENT_JOURNAL_FILL);

	num_blocks = ocfs2_blocks_for_bytes(inode->i_sb, inode->i_size);
	v_blkno = 0;
	while (v_blkno < num_blocks) {
		status = ocfs2_extent_map_get_blocks(inode, v_blkno,
						     &p_blkno, &p_blocks, NULL);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		if (p_blocks > CONCURRENT_JOURNAL_FILL)
			p_blocks = CONCURRENT_JOURNAL_FILL;

		/* We are reading journal data which should not
		 * be put in the uptodate cache */
		status = ocfs2_read_blocks_sync(OCFS2_SB(inode->i_sb),
						p_blkno, p_blocks, bhs);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		for(i = 0; i < p_blocks; i++) {
			brelse(bhs[i]);
			bhs[i] = NULL;
		}

		v_blkno += p_blocks;
	}

bail:
	for(i = 0; i < CONCURRENT_JOURNAL_FILL; i++)
		brelse(bhs[i]);
	mlog_exit(status);
	return status;
}