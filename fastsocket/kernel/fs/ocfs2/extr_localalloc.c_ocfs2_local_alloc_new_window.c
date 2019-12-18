#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct ocfs2_super {int /*<<< orphan*/  la_last_gd; int /*<<< orphan*/  osb_lock; void* local_alloc_bits; TYPE_1__* local_alloc_bh; } ;
struct ocfs2_local_alloc {void* la_bm_off; int /*<<< orphan*/  la_size; int /*<<< orphan*/  la_bitmap; } ;
struct TYPE_5__ {void* i_total; scalar_t__ i_used; } ;
struct TYPE_6__ {TYPE_2__ bitmap1; } ;
struct ocfs2_dinode {TYPE_3__ id1; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_last_group; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ OCFS2_LA_DISABLED ; 
 int /*<<< orphan*/  OCFS2_LA_EVENT_FRAGMENTED ; 
 struct ocfs2_local_alloc* OCFS2_LOCAL_ALLOC (struct ocfs2_dinode*) ; 
 void* cpu_to_le32 (void*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_claim_clusters (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,void*,void**,void**) ; 
 scalar_t__ ocfs2_recalc_la_window (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_local_alloc_new_window(struct ocfs2_super *osb,
					handle_t *handle,
					struct ocfs2_alloc_context *ac)
{
	int status = 0;
	u32 cluster_off, cluster_count;
	struct ocfs2_dinode *alloc = NULL;
	struct ocfs2_local_alloc *la;

	mlog_entry_void();

	alloc = (struct ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	if (alloc->id1.bitmap1.i_total)
		mlog(0, "asking me to alloc a new window over a non-empty "
		     "one\n");

	mlog(0, "Allocating %u clusters for a new window.\n",
	     osb->local_alloc_bits);

	/* Instruct the allocation code to try the most recently used
	 * cluster group. We'll re-record the group used this pass
	 * below. */
	ac->ac_last_group = osb->la_last_gd;

	/* we used the generic suballoc reserve function, but we set
	 * everything up nicely, so there's no reason why we can't use
	 * the more specific cluster api to claim bits. */
	status = ocfs2_claim_clusters(osb, handle, ac, osb->local_alloc_bits,
				      &cluster_off, &cluster_count);
	if (status == -ENOSPC) {
retry_enospc:
		/*
		 * Note: We could also try syncing the journal here to
		 * allow use of any free bits which the current
		 * transaction can't give us access to. --Mark
		 */
		if (ocfs2_recalc_la_window(osb, OCFS2_LA_EVENT_FRAGMENTED) ==
		    OCFS2_LA_DISABLED)
			goto bail;

		status = ocfs2_claim_clusters(osb, handle, ac,
					      osb->local_alloc_bits,
					      &cluster_off,
					      &cluster_count);
		if (status == -ENOSPC)
			goto retry_enospc;
		/*
		 * We only shrunk the *minimum* number of in our
		 * request - it's entirely possible that the allocator
		 * might give us more than we asked for.
		 */
		if (status == 0) {
			spin_lock(&osb->osb_lock);
			osb->local_alloc_bits = cluster_count;
			spin_unlock(&osb->osb_lock);
		}
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	osb->la_last_gd = ac->ac_last_group;

	la->la_bm_off = cpu_to_le32(cluster_off);
	alloc->id1.bitmap1.i_total = cpu_to_le32(cluster_count);
	/* just in case... In the future when we find space ourselves,
	 * we don't have to get all contiguous -- but we'll have to
	 * set all previously used bits in bitmap and update
	 * la_bits_set before setting the bits in the main bitmap. */
	alloc->id1.bitmap1.i_used = 0;
	memset(OCFS2_LOCAL_ALLOC(alloc)->la_bitmap, 0,
	       le16_to_cpu(la->la_size));

	mlog(0, "New window allocated:\n");
	mlog(0, "window la_bm_off = %u\n",
	     OCFS2_LOCAL_ALLOC(alloc)->la_bm_off);
	mlog(0, "window bits = %u\n", le32_to_cpu(alloc->id1.bitmap1.i_total));

bail:
	mlog_exit(status);
	return status;
}