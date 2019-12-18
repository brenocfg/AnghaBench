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
struct ocfs2_write_ctxt {int w_clen; scalar_t__ w_cpos; scalar_t__ w_first_new_cpos; struct ocfs2_write_cluster_desc* w_desc; } ;
struct ocfs2_write_cluster_desc {scalar_t__ c_cpos; int c_needs_zero; int c_new; int c_unwritten; scalar_t__ c_phys; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 unsigned int OCFS2_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_get_clusters (struct inode*,scalar_t__,scalar_t__*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int ocfs2_populate_write_desc(struct inode *inode,
				     struct ocfs2_write_ctxt *wc,
				     unsigned int *clusters_to_alloc,
				     unsigned int *extents_to_split)
{
	int ret;
	struct ocfs2_write_cluster_desc *desc;
	unsigned int num_clusters = 0;
	unsigned int ext_flags = 0;
	u32 phys = 0;
	int i;

	*clusters_to_alloc = 0;
	*extents_to_split = 0;

	for (i = 0; i < wc->w_clen; i++) {
		desc = &wc->w_desc[i];
		desc->c_cpos = wc->w_cpos + i;

		if (num_clusters == 0) {
			/*
			 * Need to look up the next extent record.
			 */
			ret = ocfs2_get_clusters(inode, desc->c_cpos, &phys,
						 &num_clusters, &ext_flags);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			/* We should already CoW the refcountd extent. */
			BUG_ON(ext_flags & OCFS2_EXT_REFCOUNTED);

			/*
			 * Assume worst case - that we're writing in
			 * the middle of the extent.
			 *
			 * We can assume that the write proceeds from
			 * left to right, in which case the extent
			 * insert code is smart enough to coalesce the
			 * next splits into the previous records created.
			 */
			if (ext_flags & OCFS2_EXT_UNWRITTEN)
				*extents_to_split = *extents_to_split + 2;
		} else if (phys) {
			/*
			 * Only increment phys if it doesn't describe
			 * a hole.
			 */
			phys++;
		}

		/*
		 * If w_first_new_cpos is < UINT_MAX, we have a non-sparse
		 * file that got extended.  w_first_new_cpos tells us
		 * where the newly allocated clusters are so we can
		 * zero them.
		 */
		if (desc->c_cpos >= wc->w_first_new_cpos) {
			BUG_ON(phys == 0);
			desc->c_needs_zero = 1;
		}

		desc->c_phys = phys;
		if (phys == 0) {
			desc->c_new = 1;
			desc->c_needs_zero = 1;
			*clusters_to_alloc = *clusters_to_alloc + 1;
		}

		if (ext_flags & OCFS2_EXT_UNWRITTEN) {
			desc->c_unwritten = 1;
			desc->c_needs_zero = 1;
		}

		num_clusters--;
	}

	ret = 0;
out:
	return ret;
}