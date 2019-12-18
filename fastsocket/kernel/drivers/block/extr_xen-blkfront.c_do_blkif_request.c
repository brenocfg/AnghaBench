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
struct request_queue {int dummy; } ;
struct request {scalar_t__ cmd_type; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cmd; TYPE_1__* rq_disk; } ;
struct blkfront_info {int /*<<< orphan*/  ring; } ;
struct TYPE_2__ {struct blkfront_info* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ REQ_TYPE_FS ; 
 scalar_t__ RING_FULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_rq_cur_sectors (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 scalar_t__ blkif_queue_request (struct request*) ; 
 int /*<<< orphan*/  flush_requests (struct blkfront_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static void do_blkif_request(struct request_queue *rq)
{
	struct blkfront_info *info = NULL;
	struct request *req;
	int queued;

	pr_debug("Entered do_blkif_request\n");

	queued = 0;

	while ((req = blk_peek_request(rq)) != NULL) {
		info = req->rq_disk->private_data;

		if (RING_FULL(&info->ring))
			goto wait;

		blk_start_request(req);

		if (req->cmd_type != REQ_TYPE_FS) {
			__blk_end_request_all(req, -EIO);
			continue;
		}

		pr_debug("do_blk_req %p: cmd %p, sec %lx, "
			 "(%u/%u) buffer:%p [%s]\n",
			 req, req->cmd, (unsigned long)blk_rq_pos(req),
			 blk_rq_cur_sectors(req), blk_rq_sectors(req),
			 req->buffer, rq_data_dir(req) ? "write" : "read");

		if (blkif_queue_request(req)) {
			blk_requeue_request(rq, req);
wait:
			/* Avoid pointless unplugs. */
			blk_stop_queue(rq);
			break;
		}

		queued++;
	}

	if (queued != 0)
		flush_requests(info);
}