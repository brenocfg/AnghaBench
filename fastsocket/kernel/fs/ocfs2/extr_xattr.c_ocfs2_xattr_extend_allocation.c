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
typedef  scalar_t__ u32 ;
struct ocfs2_xattr_value_buf {int (* vb_access ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* vb_xv; int /*<<< orphan*/  vb_bh; } ;
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  meta_ac; int /*<<< orphan*/  data_ac; int /*<<< orphan*/ * handle; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  enum ocfs2_alloc_restarted { ____Placeholder_ocfs2_alloc_restarted } ocfs2_alloc_restarted ;
struct TYPE_2__ {int /*<<< orphan*/  xr_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int RESTART_NONE ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_clusters_in_btree (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_value_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct ocfs2_xattr_value_buf*) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_extend_allocation(struct inode *inode,
					 u32 clusters_to_add,
					 struct ocfs2_xattr_value_buf *vb,
					 struct ocfs2_xattr_set_ctxt *ctxt)
{
	int status = 0;
	handle_t *handle = ctxt->handle;
	enum ocfs2_alloc_restarted why;
	u32 prev_clusters, logical_start = le32_to_cpu(vb->vb_xv->xr_clusters);
	struct ocfs2_extent_tree et;

	mlog(0, "(clusters_to_add for xattr= %u)\n", clusters_to_add);

	ocfs2_init_xattr_value_extent_tree(&et, INODE_CACHE(inode), vb);

	status = vb->vb_access(handle, INODE_CACHE(inode), vb->vb_bh,
			      OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	prev_clusters = le32_to_cpu(vb->vb_xv->xr_clusters);
	status = ocfs2_add_clusters_in_btree(handle,
					     &et,
					     &logical_start,
					     clusters_to_add,
					     0,
					     ctxt->data_ac,
					     ctxt->meta_ac,
					     &why);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_journal_dirty(handle, vb->vb_bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	clusters_to_add -= le32_to_cpu(vb->vb_xv->xr_clusters) - prev_clusters;

	/*
	 * We should have already allocated enough space before the transaction,
	 * so no need to restart.
	 */
	BUG_ON(why != RESTART_NONE || clusters_to_add);

leave:

	return status;
}