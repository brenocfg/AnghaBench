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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct super_block {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int ip_clusters; int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int EDQUOT ; 
 int EIO ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_add_inode_data (int /*<<< orphan*/ ,struct inode*,int*,int,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_blocks_for_bytes (struct super_block*,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_bytes (struct super_block*,int) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_dq_alloc_space_nodirty (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  vfs_dq_free_space_nodirty (struct inode*,scalar_t__) ; 

__attribute__((used)) static int ocfs2_do_extend_dir(struct super_block *sb,
			       handle_t *handle,
			       struct inode *dir,
			       struct buffer_head *parent_fe_bh,
			       struct ocfs2_alloc_context *data_ac,
			       struct ocfs2_alloc_context *meta_ac,
			       struct buffer_head **new_bh)
{
	int status;
	int extend, did_quota = 0;
	u64 p_blkno, v_blkno;

	spin_lock(&OCFS2_I(dir)->ip_lock);
	extend = (i_size_read(dir) == ocfs2_clusters_to_bytes(sb, OCFS2_I(dir)->ip_clusters));
	spin_unlock(&OCFS2_I(dir)->ip_lock);

	if (extend) {
		u32 offset = OCFS2_I(dir)->ip_clusters;

		if (vfs_dq_alloc_space_nodirty(dir,
					ocfs2_clusters_to_bytes(sb, 1))) {
			status = -EDQUOT;
			goto bail;
		}
		did_quota = 1;

		status = ocfs2_add_inode_data(OCFS2_SB(sb), dir, &offset,
					      1, 0, parent_fe_bh, handle,
					      data_ac, meta_ac, NULL);
		BUG_ON(status == -EAGAIN);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	v_blkno = ocfs2_blocks_for_bytes(sb, i_size_read(dir));
	status = ocfs2_extent_map_get_blocks(dir, v_blkno, &p_blkno, NULL, NULL);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	*new_bh = sb_getblk(sb, p_blkno);
	if (!*new_bh) {
		status = -EIO;
		mlog_errno(status);
		goto bail;
	}
	status = 0;
bail:
	if (did_quota && status < 0)
		vfs_dq_free_space_nodirty(dir, ocfs2_clusters_to_bytes(sb, 1));
	mlog_exit(status);
	return status;
}