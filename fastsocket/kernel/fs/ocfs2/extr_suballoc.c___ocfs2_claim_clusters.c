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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap_data; int /*<<< orphan*/  local_data; } ;
struct ocfs2_super {int bitmap_cpg; TYPE_1__ alloc_stats; } ;
struct ocfs2_alloc_context {scalar_t__ ac_bits_given; scalar_t__ ac_bits_wanted; scalar_t__ ac_which; int /*<<< orphan*/  ac_inode; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ OCFS2_AC_USE_LOCAL ; 
 scalar_t__ OCFS2_AC_USE_MAIN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_claim_local_alloc_bits (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,unsigned int,int*,int*) ; 
 int ocfs2_claim_suballoc_bits (struct ocfs2_super*,struct ocfs2_alloc_context*,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int ocfs2_desc_bitmap_to_cluster_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __ocfs2_claim_clusters(struct ocfs2_super *osb,
			   handle_t *handle,
			   struct ocfs2_alloc_context *ac,
			   u32 min_clusters,
			   u32 max_clusters,
			   u32 *cluster_start,
			   u32 *num_clusters)
{
	int status;
	unsigned int bits_wanted = max_clusters;
	u64 bg_blkno = 0;
	u16 bg_bit_off;

	mlog_entry_void();

	BUG_ON(ac->ac_bits_given >= ac->ac_bits_wanted);

	BUG_ON(ac->ac_which != OCFS2_AC_USE_LOCAL
	       && ac->ac_which != OCFS2_AC_USE_MAIN);

	if (ac->ac_which == OCFS2_AC_USE_LOCAL) {
		status = ocfs2_claim_local_alloc_bits(osb,
						      handle,
						      ac,
						      bits_wanted,
						      cluster_start,
						      num_clusters);
		if (!status)
			atomic_inc(&osb->alloc_stats.local_data);
	} else {
		if (min_clusters > (osb->bitmap_cpg - 1)) {
			/* The only paths asking for contiguousness
			 * should know about this already. */
			mlog(ML_ERROR, "minimum allocation requested %u exceeds "
			     "group bitmap size %u!\n", min_clusters,
			     osb->bitmap_cpg);
			status = -ENOSPC;
			goto bail;
		}
		/* clamp the current request down to a realistic size. */
		if (bits_wanted > (osb->bitmap_cpg - 1))
			bits_wanted = osb->bitmap_cpg - 1;

		status = ocfs2_claim_suballoc_bits(osb,
						   ac,
						   handle,
						   bits_wanted,
						   min_clusters,
						   &bg_bit_off,
						   num_clusters,
						   &bg_blkno);
		if (!status) {
			*cluster_start =
				ocfs2_desc_bitmap_to_cluster_off(ac->ac_inode,
								 bg_blkno,
								 bg_bit_off);
			atomic_inc(&osb->alloc_stats.bitmap_data);
		}
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	ac->ac_bits_given += *num_clusters;

bail:
	mlog_exit(status);
	return status;
}