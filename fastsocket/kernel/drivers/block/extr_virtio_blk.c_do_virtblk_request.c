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
struct virtio_blk {scalar_t__ sg_elems; int /*<<< orphan*/  vq; } ;
struct request_queue {struct virtio_blk* queuedata; } ;
struct request {scalar_t__ nr_phys_segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 int /*<<< orphan*/  do_req (struct request_queue*,struct virtio_blk*,struct request*) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_virtblk_request(struct request_queue *q)
{
	struct virtio_blk *vblk = q->queuedata;
	struct request *req;
	unsigned int issued = 0;

	while ((req = blk_peek_request(q)) != NULL) {
		BUG_ON(req->nr_phys_segments + 2 > vblk->sg_elems);

		/* If this request fails, stop queue and wait for something to
		   finish to restart it. */
		if (!do_req(q, vblk, req)) {
			blk_stop_queue(q);
			break;
		}
		blk_start_request(req);
		issued++;
	}

	if (issued)
		virtqueue_kick(vblk->vq);
}