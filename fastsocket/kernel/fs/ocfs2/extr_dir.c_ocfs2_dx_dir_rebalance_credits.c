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
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_list; } ;

/* Variables and functions */
 scalar_t__ ocfs2_calc_extend_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ocfs2_quota_trans_credits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dx_dir_rebalance_credits(struct ocfs2_super *osb,
					  struct ocfs2_dx_root_block *dx_root)
{
	int credits = ocfs2_clusters_to_blocks(osb->sb, 2);

	credits += ocfs2_calc_extend_credits(osb->sb, &dx_root->dr_list, 1);
	credits += ocfs2_quota_trans_credits(osb->sb);
	return credits;
}