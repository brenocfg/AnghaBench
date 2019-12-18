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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_alloc_context {unsigned int ac_bits_wanted; unsigned int ac_bits_given; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int __ocfs2_claim_clusters (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ocfs2_claim_clusters(struct ocfs2_super *osb,
			 handle_t *handle,
			 struct ocfs2_alloc_context *ac,
			 u32 min_clusters,
			 u32 *cluster_start,
			 u32 *num_clusters)
{
	unsigned int bits_wanted = ac->ac_bits_wanted - ac->ac_bits_given;

	return __ocfs2_claim_clusters(osb, handle, ac, min_clusters,
				      bits_wanted, cluster_start, num_clusters);
}