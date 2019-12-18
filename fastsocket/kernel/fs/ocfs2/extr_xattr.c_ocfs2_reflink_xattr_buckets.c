#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_xattr_value_buf {int /*<<< orphan*/  vb_access; } ;
struct ocfs2_reflink_xattr_tree_args {TYPE_2__* new_bucket; TYPE_2__* old_bucket; TYPE_5__* reflink; } ;
struct ocfs2_alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_16__ {int /*<<< orphan*/  xh_num_buckets; } ;
struct TYPE_15__ {TYPE_1__* old_inode; } ;
struct TYPE_14__ {int bu_blocks; int /*<<< orphan*/ * bu_bhs; } ;
struct TYPE_13__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  bucket_block (TYPE_2__*,int) ; 
 TYPE_6__* bucket_xh (TYPE_2__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_get_reflink_xattr_value_root ; 
 int ocfs2_init_xattr_bucket (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocfs2_journal_access ; 
 int ocfs2_read_xattr_bucket (TYPE_2__*,int) ; 
 int ocfs2_reflink_xattr_header (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,TYPE_6__*,struct ocfs2_xattr_value_buf*,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,struct ocfs2_reflink_xattr_tree_args*) ; 
 int ocfs2_xattr_bucket_journal_access (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_journal_dirty (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (TYPE_2__*) ; 
 int ocfs2_xattr_buckets_per_cluster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_reflink_xattr_buckets(handle_t *handle,
				u64 blkno, u64 new_blkno, u32 clusters,
				struct ocfs2_alloc_context *meta_ac,
				struct ocfs2_alloc_context *data_ac,
				struct ocfs2_reflink_xattr_tree_args *args)
{
	int i, j, ret = 0;
	struct super_block *sb = args->reflink->old_inode->i_sb;
	u32 bpc = ocfs2_xattr_buckets_per_cluster(OCFS2_SB(sb));
	u32 num_buckets = clusters * bpc;
	int bpb = args->old_bucket->bu_blocks;
	struct ocfs2_xattr_value_buf vb = {
		.vb_access = ocfs2_journal_access,
	};

	for (i = 0; i < num_buckets; i++, blkno += bpb, new_blkno += bpb) {
		ret = ocfs2_read_xattr_bucket(args->old_bucket, blkno);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		ret = ocfs2_init_xattr_bucket(args->new_bucket, new_blkno);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		/*
		 * The real bucket num in this series of blocks is stored
		 * in the 1st bucket.
		 */
		if (i == 0)
			num_buckets = le16_to_cpu(
				bucket_xh(args->old_bucket)->xh_num_buckets);

		ret = ocfs2_xattr_bucket_journal_access(handle,
						args->new_bucket,
						OCFS2_JOURNAL_ACCESS_CREATE);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		for (j = 0; j < bpb; j++)
			memcpy(bucket_block(args->new_bucket, j),
			       bucket_block(args->old_bucket, j),
			       sb->s_blocksize);

		ocfs2_xattr_bucket_journal_dirty(handle, args->new_bucket);

		ret = ocfs2_reflink_xattr_header(handle, args->reflink,
					args->old_bucket->bu_bhs[0],
					bucket_xh(args->old_bucket),
					args->new_bucket->bu_bhs[0],
					bucket_xh(args->new_bucket),
					&vb, meta_ac,
					ocfs2_get_reflink_xattr_value_root,
					args);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		/*
		 * Re-access and dirty the bucket to calculate metaecc.
		 * Because we may extend the transaction in reflink_xattr_header
		 * which will let the already accessed block gone.
		 */
		ret = ocfs2_xattr_bucket_journal_access(handle,
						args->new_bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		ocfs2_xattr_bucket_journal_dirty(handle, args->new_bucket);
		ocfs2_xattr_bucket_relse(args->old_bucket);
		ocfs2_xattr_bucket_relse(args->new_bucket);
	}

	ocfs2_xattr_bucket_relse(args->old_bucket);
	ocfs2_xattr_bucket_relse(args->new_bucket);
	return ret;
}