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
typedef  scalar_t__ u32 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_cow_context {scalar_t__ cow_start; scalar_t__ cow_len; int (* get_clusters ) (struct ocfs2_cow_context*,scalar_t__,scalar_t__*,scalar_t__*,unsigned int*) ;int /*<<< orphan*/  dealloc; struct inode* inode; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EROFS ; 
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_dealloc_has_cluster (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (int /*<<< orphan*/ *) ; 
 int ocfs2_make_clusters_writable (int /*<<< orphan*/ ,struct ocfs2_cow_context*,scalar_t__,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int stub1 (struct ocfs2_cow_context*,scalar_t__,scalar_t__*,scalar_t__*,unsigned int*) ; 

__attribute__((used)) static int ocfs2_replace_cow(struct ocfs2_cow_context *context)
{
	int ret = 0;
	struct inode *inode = context->inode;
	u32 cow_start = context->cow_start, cow_len = context->cow_len;
	u32 p_cluster, num_clusters;
	unsigned int ext_flags;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb))) {
		ocfs2_error(inode->i_sb, "Inode %lu want to use refcount "
			    "tree, but the feature bit is not set in the "
			    "super block.", inode->i_ino);
		return -EROFS;
	}

	ocfs2_init_dealloc_ctxt(&context->dealloc);

	while (cow_len) {
		ret = context->get_clusters(context, cow_start, &p_cluster,
					    &num_clusters, &ext_flags);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		BUG_ON(!(ext_flags & OCFS2_EXT_REFCOUNTED));

		if (cow_len < num_clusters)
			num_clusters = cow_len;

		ret = ocfs2_make_clusters_writable(inode->i_sb, context,
						   cow_start, p_cluster,
						   num_clusters, ext_flags);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		cow_len -= num_clusters;
		cow_start += num_clusters;
	}

	if (ocfs2_dealloc_has_cluster(&context->dealloc)) {
		ocfs2_schedule_truncate_log_flush(osb, 1);
		ocfs2_run_deallocs(osb, &context->dealloc);
	}

	return ret;
}