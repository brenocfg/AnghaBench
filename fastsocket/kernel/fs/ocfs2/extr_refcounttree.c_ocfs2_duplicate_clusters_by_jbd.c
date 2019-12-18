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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct TYPE_4__ {struct ocfs2_caching_info* et_ci; } ;
struct ocfs2_cow_context {TYPE_2__ data_et; TYPE_1__* inode; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 void* ocfs2_clusters_to_blocks (struct super_block*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_read_block (struct ocfs2_caching_info*,void*,struct buffer_head**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (struct ocfs2_caching_info*,struct buffer_head*) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int ocfs2_duplicate_clusters_by_jbd(handle_t *handle,
					   struct ocfs2_cow_context *context,
					   u32 cpos, u32 old_cluster,
					   u32 new_cluster, u32 new_len)
{
	int ret = 0;
	struct super_block *sb = context->inode->i_sb;
	struct ocfs2_caching_info *ci = context->data_et.et_ci;
	int i, blocks = ocfs2_clusters_to_blocks(sb, new_len);
	u64 old_block = ocfs2_clusters_to_blocks(sb, old_cluster);
	u64 new_block = ocfs2_clusters_to_blocks(sb, new_cluster);
	struct ocfs2_super *osb = OCFS2_SB(sb);
	struct buffer_head *old_bh = NULL;
	struct buffer_head *new_bh = NULL;

	mlog(0, "old_cluster %u, new %u, len %u\n", old_cluster,
	     new_cluster, new_len);

	for (i = 0; i < blocks; i++, old_block++, new_block++) {
		new_bh = sb_getblk(osb->sb, new_block);
		if (new_bh == NULL) {
			ret = -EIO;
			mlog_errno(ret);
			break;
		}

		ocfs2_set_new_buffer_uptodate(ci, new_bh);

		ret = ocfs2_read_block(ci, old_block, &old_bh, NULL);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		ret = ocfs2_journal_access(handle, ci, new_bh,
					   OCFS2_JOURNAL_ACCESS_CREATE);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		memcpy(new_bh->b_data, old_bh->b_data, sb->s_blocksize);
		ret = ocfs2_journal_dirty(handle, new_bh);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		brelse(new_bh);
		brelse(old_bh);
		new_bh = NULL;
		old_bh = NULL;
	}

	brelse(new_bh);
	brelse(old_bh);
	return ret;
}