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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_max_block; int /*<<< orphan*/  ac_bits_wanted; } ;

/* Variables and functions */
 int ALLOC_GROUPS_FROM_GLOBAL ; 
 int EFBIG ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocfs2_alloc_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_alloc_should_use_local (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_reserve_cluster_bitmap_bits (struct ocfs2_super*,struct ocfs2_alloc_context*) ; 
 int ocfs2_reserve_local_alloc_bits (struct ocfs2_super*,int /*<<< orphan*/ ,struct ocfs2_alloc_context*) ; 

__attribute__((used)) static int ocfs2_reserve_clusters_with_limit(struct ocfs2_super *osb,
					     u32 bits_wanted, u64 max_block,
					     int flags,
					     struct ocfs2_alloc_context **ac)
{
	int status;

	mlog_entry_void();

	*ac = kzalloc(sizeof(struct ocfs2_alloc_context), GFP_KERNEL);
	if (!(*ac)) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	(*ac)->ac_bits_wanted = bits_wanted;
	(*ac)->ac_max_block = max_block;

	status = -ENOSPC;
	if (!(flags & ALLOC_GROUPS_FROM_GLOBAL) &&
	    ocfs2_alloc_should_use_local(osb, bits_wanted)) {
		status = ocfs2_reserve_local_alloc_bits(osb,
							bits_wanted,
							*ac);
		if (status == -EFBIG) {
			/* The local alloc window is outside ac_max_block.
			 * use the main bitmap. */
			status = -ENOSPC;
		} else if ((status < 0) && (status != -ENOSPC)) {
			mlog_errno(status);
			goto bail;
		}
	}

	if (status == -ENOSPC) {
		status = ocfs2_reserve_cluster_bitmap_bits(osb, *ac);
		if (status < 0) {
			if (status != -ENOSPC)
				mlog_errno(status);
			goto bail;
		}
	}

	status = 0;
bail:
	if ((status < 0) && *ac) {
		ocfs2_free_alloc_context(*ac);
		*ac = NULL;
	}

	mlog_exit(status);
	return status;
}