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
struct ocfs2_dir_block_trailer {unsigned long long db_signature; int /*<<< orphan*/  db_blkno; int /*<<< orphan*/  db_parent_dinode; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DIR_TRAILER (struct ocfs2_dir_block_trailer*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,...) ; 
 struct ocfs2_dir_block_trailer* ocfs2_trailer_from_bh (struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_check_dir_trailer(struct inode *dir, struct buffer_head *bh)
{
	int rc = 0;
	struct ocfs2_dir_block_trailer *trailer;

	trailer = ocfs2_trailer_from_bh(bh, dir->i_sb);
	if (!OCFS2_IS_VALID_DIR_TRAILER(trailer)) {
		rc = -EINVAL;
		ocfs2_error(dir->i_sb,
			    "Invalid dirblock #%llu: "
			    "signature = %.*s\n",
			    (unsigned long long)bh->b_blocknr, 7,
			    trailer->db_signature);
		goto out;
	}
	if (le64_to_cpu(trailer->db_blkno) != bh->b_blocknr) {
		rc = -EINVAL;
		ocfs2_error(dir->i_sb,
			    "Directory block #%llu has an invalid "
			    "db_blkno of %llu",
			    (unsigned long long)bh->b_blocknr,
			    (unsigned long long)le64_to_cpu(trailer->db_blkno));
		goto out;
	}
	if (le64_to_cpu(trailer->db_parent_dinode) !=
	    OCFS2_I(dir)->ip_blkno) {
		rc = -EINVAL;
		ocfs2_error(dir->i_sb,
			    "Directory block #%llu on dinode "
			    "#%llu has an invalid parent_dinode "
			    "of %llu",
			    (unsigned long long)bh->b_blocknr,
			    (unsigned long long)OCFS2_I(dir)->ip_blkno,
			    (unsigned long long)le64_to_cpu(trailer->db_blkno));
		goto out;
	}
out:
	return rc;
}