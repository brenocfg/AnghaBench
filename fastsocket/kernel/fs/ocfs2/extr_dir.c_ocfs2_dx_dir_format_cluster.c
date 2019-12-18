#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_super {TYPE_2__* sb; int /*<<< orphan*/  fs_generation; } ;
struct TYPE_5__ {int /*<<< orphan*/  de_count; } ;
struct ocfs2_dx_leaf {TYPE_1__ dl_list; int /*<<< orphan*/  dl_blkno; int /*<<< orphan*/  dl_fs_generation; int /*<<< orphan*/  dl_signature; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_7__ {scalar_t__ ip_blkno; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_DX_LEAF_SIGNATURE ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_dx_leaf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_dx_entries_per_leaf (TYPE_2__*) ; 
 int ocfs2_journal_access_dl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 struct buffer_head* sb_getblk (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dx_dir_format_cluster(struct ocfs2_super *osb,
				       handle_t *handle, struct inode *dir,
				       struct buffer_head **dx_leaves,
				       int num_dx_leaves, u64 start_blk)
{
	int ret, i;
	struct ocfs2_dx_leaf *dx_leaf;
	struct buffer_head *bh;

	for (i = 0; i < num_dx_leaves; i++) {
		bh = sb_getblk(osb->sb, start_blk + i);
		if (bh == NULL) {
			ret = -EIO;
			goto out;
		}
		dx_leaves[i] = bh;

		ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), bh);

		ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir), bh,
					      OCFS2_JOURNAL_ACCESS_CREATE);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		dx_leaf = (struct ocfs2_dx_leaf *) bh->b_data;

		memset(dx_leaf, 0, osb->sb->s_blocksize);
		strcpy(dx_leaf->dl_signature, OCFS2_DX_LEAF_SIGNATURE);
		dx_leaf->dl_fs_generation = cpu_to_le32(osb->fs_generation);
		dx_leaf->dl_blkno = cpu_to_le64(bh->b_blocknr);
		dx_leaf->dl_list.de_count =
			cpu_to_le16(ocfs2_dx_entries_per_leaf(osb->sb));

		mlog(0,
		     "Dir %llu, format dx_leaf: %llu, entry count: %u\n",
		     (unsigned long long)OCFS2_I(dir)->ip_blkno,
		     (unsigned long long)bh->b_blocknr,
		     le16_to_cpu(dx_leaf->dl_list.de_count));

		ocfs2_journal_dirty(handle, bh);
	}

	ret = 0;
out:
	return ret;
}