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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_disk_dqtrailer {int /*<<< orphan*/  dq_check; } ;
struct buffer_head {int /*<<< orphan*/  b_data; scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 struct ocfs2_disk_dqtrailer* ocfs2_block_dqtrailer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_validate_quota_block(struct super_block *sb,
				      struct buffer_head *bh)
{
	struct ocfs2_disk_dqtrailer *dqt =
		ocfs2_block_dqtrailer(sb->s_blocksize, bh->b_data);

	mlog(0, "Validating quota block %llu\n",
	     (unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we return the error but otherwise
	 * leave the filesystem running.  We know any error is
	 * local to this block.
	 */
	return ocfs2_validate_meta_ecc(sb, bh->b_data, &dqt->dq_check);
}