#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  generation; int /*<<< orphan*/  type; } ;
struct pending_request {TYPE_2__ req; struct file_info* file_info; } ;
struct file_info {int /*<<< orphan*/  reqlists_lock; TYPE_1__* iso_handle; int /*<<< orphan*/  host; } ;
struct TYPE_3__ {int /*<<< orphan*/  overflows; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RAW1394_REQ_RAWISO_ACTIVITY ; 
 struct pending_request* __alloc_pending_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __queue_complete_req (struct pending_request*) ; 
 int /*<<< orphan*/  __rawiso_event_in_queue (struct file_info*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hpsb_generation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_rawiso_event(struct file_info *fi)
{
	unsigned long flags;

	spin_lock_irqsave(&fi->reqlists_lock, flags);

	/* only one ISO activity event may be in the queue */
	if (!__rawiso_event_in_queue(fi)) {
		struct pending_request *req =
		    __alloc_pending_request(GFP_ATOMIC);

		if (req) {
			req->file_info = fi;
			req->req.type = RAW1394_REQ_RAWISO_ACTIVITY;
			req->req.generation = get_hpsb_generation(fi->host);
			__queue_complete_req(req);
		} else {
			/* on allocation failure, signal an overflow */
			if (fi->iso_handle) {
				atomic_inc(&fi->iso_handle->overflows);
			}
		}
	}
	spin_unlock_irqrestore(&fi->reqlists_lock, flags);
}