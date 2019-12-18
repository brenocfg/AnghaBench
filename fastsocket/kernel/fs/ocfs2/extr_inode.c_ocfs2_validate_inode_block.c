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
struct super_block {int dummy; } ;
struct ocfs2_dinode {int i_flags; int /*<<< orphan*/  i_fs_generation; int /*<<< orphan*/  i_blkno; int /*<<< orphan*/  i_signature; int /*<<< orphan*/  i_check; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
struct TYPE_2__ {unsigned long long fs_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  OCFS2_VALID_FL ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_error (struct super_block*,char*,unsigned long long,...) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 

int ocfs2_validate_inode_block(struct super_block *sb,
			       struct buffer_head *bh)
{
	int rc;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)bh->b_data;

	mlog(0, "Validating dinode %llu\n",
	     (unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we return the error but otherwise
	 * leave the filesystem running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &di->i_check);
	if (rc) {
		mlog(ML_ERROR, "Checksum failed for dinode %llu\n",
		     (unsigned long long)bh->b_blocknr);
		goto bail;
	}

	/*
	 * Errors after here are fatal.
	 */

	rc = -EINVAL;

	if (!OCFS2_IS_VALID_DINODE(di)) {
		ocfs2_error(sb, "Invalid dinode #%llu: signature = %.*s\n",
			    (unsigned long long)bh->b_blocknr, 7,
			    di->i_signature);
		goto bail;
	}

	if (le64_to_cpu(di->i_blkno) != bh->b_blocknr) {
		ocfs2_error(sb, "Invalid dinode #%llu: i_blkno is %llu\n",
			    (unsigned long long)bh->b_blocknr,
			    (unsigned long long)le64_to_cpu(di->i_blkno));
		goto bail;
	}

	if (!(di->i_flags & cpu_to_le32(OCFS2_VALID_FL))) {
		ocfs2_error(sb,
			    "Invalid dinode #%llu: OCFS2_VALID_FL not set\n",
			    (unsigned long long)bh->b_blocknr);
		goto bail;
	}

	if (le32_to_cpu(di->i_fs_generation) !=
	    OCFS2_SB(sb)->fs_generation) {
		ocfs2_error(sb,
			    "Invalid dinode #%llu: fs_generation is %u\n",
			    (unsigned long long)bh->b_blocknr,
			    le32_to_cpu(di->i_fs_generation));
		goto bail;
	}

	rc = 0;

bail:
	return rc;
}