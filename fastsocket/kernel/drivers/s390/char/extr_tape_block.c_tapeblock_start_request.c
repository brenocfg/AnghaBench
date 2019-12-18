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
struct tape_request {int /*<<< orphan*/  retries; void* callback_data; int /*<<< orphan*/  callback; } ;
struct tape_device {TYPE_1__* discipline; } ;
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_bread ) (struct tape_request*) ;struct tape_request* (* bread ) (struct tape_device*,struct request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,struct tape_device*,struct request*) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TAPEBLOCK_RETRIES ; 
 int /*<<< orphan*/  __tapeblock_end_request ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct tape_request* stub1 (struct tape_device*,struct request*) ; 
 int /*<<< orphan*/  stub2 (struct tape_request*) ; 
 int tape_do_io_async (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static int
tapeblock_start_request(struct tape_device *device, struct request *req)
{
	struct tape_request *	ccw_req;
	int			rc;

	DBF_LH(6, "tapeblock_start_request(%p, %p)\n", device, req);

	ccw_req = device->discipline->bread(device, req);
	if (IS_ERR(ccw_req)) {
		DBF_EVENT(1, "TBLOCK: bread failed\n");
		blk_end_request_all(req, -EIO);
		return PTR_ERR(ccw_req);
	}
	ccw_req->callback = __tapeblock_end_request;
	ccw_req->callback_data = (void *) req;
	ccw_req->retries = TAPEBLOCK_RETRIES;

	rc = tape_do_io_async(device, ccw_req);
	if (rc) {
		/*
		 * Start/enqueueing failed. No retries in
		 * this case.
		 */
		blk_end_request_all(req, -EIO);
		device->discipline->free_bread(ccw_req);
	}

	return rc;
}