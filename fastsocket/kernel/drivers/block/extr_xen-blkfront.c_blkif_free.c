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
struct TYPE_2__ {int /*<<< orphan*/ * sring; } ;
struct blkfront_info {scalar_t__ ring_ref; scalar_t__ irq; scalar_t__ evtchn; TYPE_1__ ring; int /*<<< orphan*/  callback; scalar_t__ rq; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  BLKIF_STATE_SUSPENDED ; 
 scalar_t__ GRANT_INVALID_REF ; 
 int /*<<< orphan*/  blk_stop_queue (scalar_t__) ; 
 int /*<<< orphan*/  blkif_io_lock ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  gnttab_cancel_free_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,struct blkfront_info*) ; 

__attribute__((used)) static void blkif_free(struct blkfront_info *info, int suspend)
{
	/* Prevent new requests being issued until we fix things up. */
	spin_lock_irq(&blkif_io_lock);
	info->connected = suspend ?
		BLKIF_STATE_SUSPENDED : BLKIF_STATE_DISCONNECTED;
	/* No more blkif_request(). */
	if (info->rq)
		blk_stop_queue(info->rq);
	/* No more gnttab callback work. */
	gnttab_cancel_free_callback(&info->callback);
	spin_unlock_irq(&blkif_io_lock);

	/* Flush gnttab callback work. Must be done with no locks held. */
	flush_scheduled_work();

	/* Free resources associated with old device channel. */
	if (info->ring_ref != GRANT_INVALID_REF) {
		gnttab_end_foreign_access(info->ring_ref, 0,
					  (unsigned long)info->ring.sring);
		info->ring_ref = GRANT_INVALID_REF;
		info->ring.sring = NULL;
	}
	if (info->irq)
		unbind_from_irqhandler(info->irq, info);
	info->evtchn = info->irq = 0;

}