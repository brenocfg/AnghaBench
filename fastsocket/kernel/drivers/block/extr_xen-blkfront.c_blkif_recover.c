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
struct request {int dummy; } ;
struct blkif_request {int id; int nr_segments; TYPE_1__* seg; } ;
struct TYPE_6__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct blkfront_info {int /*<<< orphan*/  connected; TYPE_2__* xbdev; TYPE_3__ ring; struct blk_shadow* shadow; int /*<<< orphan*/  shadow_free; } ;
struct blk_shadow {scalar_t__ request; struct blkif_request req; int /*<<< orphan*/ * frame; } ;
typedef  int /*<<< orphan*/  copy ;
struct TYPE_5__ {int /*<<< orphan*/  otherend_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  gref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_STATE_CONNECTED ; 
 int BLK_RING_SIZE ; 
 int ENOMEM ; 
 int GFP_NOIO ; 
 struct blkif_request* RING_GET_REQUEST (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XenbusStateConnected ; 
 int __GFP_HIGH ; 
 int __GFP_REPEAT ; 
 int /*<<< orphan*/  blkif_io_lock ; 
 int /*<<< orphan*/  flush_requests (struct blkfront_info*) ; 
 size_t get_id_from_freelist (struct blkfront_info*) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_access_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct blk_shadow*) ; 
 int /*<<< orphan*/  kick_pending_request_queues (struct blkfront_info*) ; 
 struct blk_shadow* kmalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (struct blk_shadow*,struct blk_shadow*,int) ; 
 int /*<<< orphan*/  memset (struct blk_shadow**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfn_to_mfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_switch_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blkif_recover(struct blkfront_info *info)
{
	int i;
	struct blkif_request *req;
	struct blk_shadow *copy;
	int j;

	/* Stage 1: Make a safe copy of the shadow state. */
	copy = kmalloc(sizeof(info->shadow),
		       GFP_NOIO | __GFP_REPEAT | __GFP_HIGH);
	if (!copy)
		return -ENOMEM;
	memcpy(copy, info->shadow, sizeof(info->shadow));

	/* Stage 2: Set up free list. */
	memset(&info->shadow, 0, sizeof(info->shadow));
	for (i = 0; i < BLK_RING_SIZE; i++)
		info->shadow[i].req.id = i+1;
	info->shadow_free = info->ring.req_prod_pvt;
	info->shadow[BLK_RING_SIZE-1].req.id = 0x0fffffff;

	/* Stage 3: Find pending requests and requeue them. */
	for (i = 0; i < BLK_RING_SIZE; i++) {
		/* Not in use? */
		if (copy[i].request == 0)
			continue;

		/* Grab a request slot and copy shadow state into it. */
		req = RING_GET_REQUEST(&info->ring, info->ring.req_prod_pvt);
		*req = copy[i].req;

		/* We get a new request id, and must reset the shadow state. */
		req->id = get_id_from_freelist(info);
		memcpy(&info->shadow[req->id], &copy[i], sizeof(copy[i]));

		/* Rewrite any grant references invalidated by susp/resume. */
		for (j = 0; j < req->nr_segments; j++)
			gnttab_grant_foreign_access_ref(
				req->seg[j].gref,
				info->xbdev->otherend_id,
				pfn_to_mfn(info->shadow[req->id].frame[j]),
				rq_data_dir(
					(struct request *)
					info->shadow[req->id].request));
		info->shadow[req->id].req = *req;

		info->ring.req_prod_pvt++;
	}

	kfree(copy);

	xenbus_switch_state(info->xbdev, XenbusStateConnected);

	spin_lock_irq(&blkif_io_lock);

	/* Now safe for us to use the shared ring */
	info->connected = BLKIF_STATE_CONNECTED;

	/* Send off requeued requests */
	flush_requests(info);

	/* Kick any other new requests queued since we resumed */
	kick_pending_request_queues(info);

	spin_unlock_irq(&blkif_io_lock);

	return 0;
}