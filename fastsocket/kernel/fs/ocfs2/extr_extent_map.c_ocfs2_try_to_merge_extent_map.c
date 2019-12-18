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
struct ocfs2_extent_map_item {scalar_t__ ei_phys; scalar_t__ ei_clusters; scalar_t__ ei_cpos; scalar_t__ ei_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_copy_emi_fields (struct ocfs2_extent_map_item*,struct ocfs2_extent_map_item*) ; 
 scalar_t__ ocfs2_ei_is_contained (struct ocfs2_extent_map_item*,struct ocfs2_extent_map_item*) ; 

__attribute__((used)) static int ocfs2_try_to_merge_extent_map(struct ocfs2_extent_map_item *emi,
					 struct ocfs2_extent_map_item *ins)
{
	/*
	 * Handle contiguousness
	 */
	if (ins->ei_phys == (emi->ei_phys + emi->ei_clusters) &&
	    ins->ei_cpos == (emi->ei_cpos + emi->ei_clusters) &&
	    ins->ei_flags == emi->ei_flags) {
		emi->ei_clusters += ins->ei_clusters;
		return 1;
	} else if ((ins->ei_phys + ins->ei_clusters) == emi->ei_phys &&
		   (ins->ei_cpos + ins->ei_clusters) == emi->ei_phys &&
		   ins->ei_flags == emi->ei_flags) {
		emi->ei_phys = ins->ei_phys;
		emi->ei_cpos = ins->ei_cpos;
		emi->ei_clusters += ins->ei_clusters;
		return 1;
	}

	/*
	 * Overlapping extents - this shouldn't happen unless we've
	 * split an extent to change it's flags. That is exceedingly
	 * rare, so there's no sense in trying to optimize it yet.
	 */
	if (ocfs2_ei_is_contained(emi, ins) ||
	    ocfs2_ei_is_contained(ins, emi)) {
		ocfs2_copy_emi_fields(emi, ins);
		return 1;
	}

	/* No merge was possible. */
	return 0;
}