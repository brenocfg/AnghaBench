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
struct raw3215_req {struct ccw1* ccws; struct raw3215_info* info; int /*<<< orphan*/  type; } ;
struct raw3215_info {int /*<<< orphan*/  inbuf; struct raw3215_req* queued_read; } ;
struct ccw1 {int cmd_code; int flags; int count; scalar_t__ cda; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3215_READ ; 
 scalar_t__ __pa (int /*<<< orphan*/ ) ; 
 struct raw3215_req* raw3215_alloc_req () ; 

__attribute__((used)) static void raw3215_mk_read_req(struct raw3215_info *raw)
{
	struct raw3215_req *req;
	struct ccw1 *ccw;

	/* there can only be ONE read request at a time */
	req = raw->queued_read;
	if (req == NULL) {
		/* no queued read request, use new req structure */
		req = raw3215_alloc_req();
		req->type = RAW3215_READ;
		req->info = raw;
		raw->queued_read = req;
	}

	ccw = req->ccws;
	ccw->cmd_code = 0x0A; /* read inquiry */
	ccw->flags = 0x20;    /* ignore incorrect length */
	ccw->count = 160;
	ccw->cda = (__u32) __pa(raw->inbuf);
}