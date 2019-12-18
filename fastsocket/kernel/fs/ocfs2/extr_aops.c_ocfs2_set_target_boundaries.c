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
struct ocfs2_write_ctxt {int w_target_from; unsigned int w_target_to; int w_clen; struct ocfs2_write_cluster_desc* w_desc; scalar_t__ w_large_pages; } ;
struct ocfs2_write_cluster_desc {int /*<<< orphan*/  c_cpos; scalar_t__ c_needs_zero; } ;
struct ocfs2_super {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  ocfs2_figure_cluster_boundaries (struct ocfs2_super*,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void ocfs2_set_target_boundaries(struct ocfs2_super *osb,
					struct ocfs2_write_ctxt *wc,
					loff_t pos, unsigned len, int alloc)
{
	struct ocfs2_write_cluster_desc *desc;

	wc->w_target_from = pos & (PAGE_CACHE_SIZE - 1);
	wc->w_target_to = wc->w_target_from + len;

	if (alloc == 0)
		return;

	/*
	 * Allocating write - we may have different boundaries based
	 * on page size and cluster size.
	 *
	 * NOTE: We can no longer compute one value from the other as
	 * the actual write length and user provided length may be
	 * different.
	 */

	if (wc->w_large_pages) {
		/*
		 * We only care about the 1st and last cluster within
		 * our range and whether they should be zero'd or not. Either
		 * value may be extended out to the start/end of a
		 * newly allocated cluster.
		 */
		desc = &wc->w_desc[0];
		if (desc->c_needs_zero)
			ocfs2_figure_cluster_boundaries(osb,
							desc->c_cpos,
							&wc->w_target_from,
							NULL);

		desc = &wc->w_desc[wc->w_clen - 1];
		if (desc->c_needs_zero)
			ocfs2_figure_cluster_boundaries(osb,
							desc->c_cpos,
							NULL,
							&wc->w_target_to);
	} else {
		wc->w_target_from = 0;
		wc->w_target_to = PAGE_CACHE_SIZE;
	}
}