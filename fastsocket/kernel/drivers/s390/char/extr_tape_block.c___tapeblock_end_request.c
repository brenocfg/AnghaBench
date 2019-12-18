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
struct tape_request {scalar_t__ rc; struct tape_device* device; } ;
struct TYPE_4__ {int block_position; int /*<<< orphan*/  request_queue; } ;
struct tape_device {TYPE_2__ blk_data; int /*<<< orphan*/  req_queue; TYPE_1__* discipline; } ;
struct request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_bread ) (struct tape_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*) ; 
 int /*<<< orphan*/  EIO ; 
 int TAPEBLOCK_HSEC_S2B ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_peek_request (int /*<<< orphan*/ ) ; 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tape_request*) ; 
 int /*<<< orphan*/  tapeblock_trigger_requeue (struct tape_device*) ; 

__attribute__((used)) static void
__tapeblock_end_request(struct tape_request *ccw_req, void *data)
{
	struct tape_device *device;
	struct request *req;

	DBF_LH(6, "__tapeblock_end_request()\n");

	device = ccw_req->device;
	req = (struct request *) data;
	blk_end_request_all(req, (ccw_req->rc == 0) ? 0 : -EIO);
	if (ccw_req->rc == 0)
		/* Update position. */
		device->blk_data.block_position =
		  (blk_rq_pos(req) + blk_rq_sectors(req)) >> TAPEBLOCK_HSEC_S2B;
	else
		/* We lost the position information due to an error. */
		device->blk_data.block_position = -1;
	device->discipline->free_bread(ccw_req);
	if (!list_empty(&device->req_queue) ||
	    blk_peek_request(device->blk_data.request_queue))
		tapeblock_trigger_requeue(device);
}