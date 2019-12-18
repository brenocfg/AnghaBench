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
struct ocfs2_super {int local_alloc_state; int local_alloc_bits; unsigned int local_alloc_default_bits; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  la_enable_wq; int /*<<< orphan*/  sb; } ;
typedef  enum ocfs2_la_event { ____Placeholder_ocfs2_la_event } ocfs2_la_event ;

/* Variables and functions */
 int OCFS2_LA_DISABLED ; 
 int /*<<< orphan*/  OCFS2_LA_ENABLE_INTERVAL ; 
 int OCFS2_LA_EVENT_ENOSPC ; 
 int OCFS2_LA_EVENT_FRAGMENTED ; 
 int OCFS2_LA_THROTTLED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned int ocfs2_megabytes_to_clusters (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_recalc_la_window(struct ocfs2_super *osb,
				  enum ocfs2_la_event event)
{
	unsigned int bits;
	int state;

	spin_lock(&osb->osb_lock);
	if (osb->local_alloc_state == OCFS2_LA_DISABLED) {
		WARN_ON_ONCE(osb->local_alloc_state == OCFS2_LA_DISABLED);
		goto out_unlock;
	}

	/*
	 * ENOSPC and fragmentation are treated similarly for now.
	 */
	if (event == OCFS2_LA_EVENT_ENOSPC ||
	    event == OCFS2_LA_EVENT_FRAGMENTED) {
		/*
		 * We ran out of contiguous space in the primary
		 * bitmap. Drastically reduce the number of bits used
		 * by local alloc until we have to disable it.
		 */
		bits = osb->local_alloc_bits >> 1;
		if (bits > ocfs2_megabytes_to_clusters(osb->sb, 1)) {
			/*
			 * By setting state to THROTTLED, we'll keep
			 * the number of local alloc bits used down
			 * until an event occurs which would give us
			 * reason to assume the bitmap situation might
			 * have changed.
			 */
			osb->local_alloc_state = OCFS2_LA_THROTTLED;
			osb->local_alloc_bits = bits;
		} else {
			osb->local_alloc_state = OCFS2_LA_DISABLED;
		}
		queue_delayed_work(ocfs2_wq, &osb->la_enable_wq,
				   OCFS2_LA_ENABLE_INTERVAL);
		goto out_unlock;
	}

	/*
	 * Don't increase the size of the local alloc window until we
	 * know we might be able to fulfill the request. Otherwise, we
	 * risk bouncing around the global bitmap during periods of
	 * low space.
	 */
	if (osb->local_alloc_state != OCFS2_LA_THROTTLED)
		osb->local_alloc_bits = osb->local_alloc_default_bits;

out_unlock:
	state = osb->local_alloc_state;
	spin_unlock(&osb->osb_lock);

	return state;
}