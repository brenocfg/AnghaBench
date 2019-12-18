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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int ocfs2_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int ocfs2_validate_gd_parent (int /*<<< orphan*/ ,struct ocfs2_dinode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_validate_group_descriptor ; 

int ocfs2_read_group_descriptor(struct inode *inode, struct ocfs2_dinode *di,
				u64 gd_blkno, struct buffer_head **bh)
{
	int rc;
	struct buffer_head *tmp = *bh;

	rc = ocfs2_read_block(INODE_CACHE(inode), gd_blkno, &tmp,
			      ocfs2_validate_group_descriptor);
	if (rc)
		goto out;

	rc = ocfs2_validate_gd_parent(inode->i_sb, di, tmp, 0);
	if (rc) {
		brelse(tmp);
		goto out;
	}

	/* If ocfs2_read_block() got us a new bh, pass it up. */
	if (!*bh)
		*bh = tmp;

out:
	return rc;
}