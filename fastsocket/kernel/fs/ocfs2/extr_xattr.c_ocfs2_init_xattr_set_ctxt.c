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
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/ * meta_ac; int /*<<< orphan*/  data_ac; int /*<<< orphan*/  dealloc; } ;
struct ocfs2_xattr_search {int dummy; } ;
struct ocfs2_xattr_info {int /*<<< orphan*/  name; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_xattr_set_ctxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_calc_xattr_set_need (struct inode*,struct ocfs2_dinode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_search*,int*,int*,int*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (int /*<<< orphan*/ *) ; 
 int ocfs2_reserve_clusters (struct ocfs2_super*,int,int /*<<< orphan*/ *) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int ocfs2_init_xattr_set_ctxt(struct inode *inode,
				     struct ocfs2_dinode *di,
				     struct ocfs2_xattr_info *xi,
				     struct ocfs2_xattr_search *xis,
				     struct ocfs2_xattr_search *xbs,
				     struct ocfs2_xattr_set_ctxt *ctxt,
				     int extra_meta,
				     int *credits)
{
	int clusters_add, meta_add, ret;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	memset(ctxt, 0, sizeof(struct ocfs2_xattr_set_ctxt));

	ocfs2_init_dealloc_ctxt(&ctxt->dealloc);

	ret = ocfs2_calc_xattr_set_need(inode, di, xi, xis, xbs,
					&clusters_add, &meta_add, credits);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	meta_add += extra_meta;
	mlog(0, "Set xattr %s, reserve meta blocks = %d, clusters = %d, "
	     "credits = %d\n", xi->name, meta_add, clusters_add, *credits);

	if (meta_add) {
		ret = ocfs2_reserve_new_metadata_blocks(osb, meta_add,
							&ctxt->meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	if (clusters_add) {
		ret = ocfs2_reserve_clusters(osb, clusters_add, &ctxt->data_ac);
		if (ret)
			mlog_errno(ret);
	}
out:
	if (ret) {
		if (ctxt->meta_ac) {
			ocfs2_free_alloc_context(ctxt->meta_ac);
			ctxt->meta_ac = NULL;
		}

		/*
		 * We cannot have an error and a non null ctxt->data_ac.
		 */
	}

	return ret;
}