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
struct raw3215_req {int len; int start; int delayable; struct ccw1* ccws; struct raw3215_info* info; int /*<<< orphan*/  type; } ;
struct raw3215_info {int count; int written; int head; int* buffer; struct raw3215_req* queued_write; } ;
struct ccw1 {int flags; int cmd_code; int count; scalar_t__ cda; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int RAW3215_BUFFER_SIZE ; 
 int RAW3215_MAX_BYTES ; 
 int RAW3215_MAX_NEWLINE ; 
 int RAW3215_MIN_WRITE ; 
 int /*<<< orphan*/  RAW3215_WRITE ; 
 scalar_t__ __pa (int*) ; 
 struct raw3215_req* raw3215_alloc_req () ; 

__attribute__((used)) static void raw3215_mk_write_req(struct raw3215_info *raw)
{
	struct raw3215_req *req;
	struct ccw1 *ccw;
	int len, count, ix, lines;

	if (raw->count <= raw->written)
		return;
	/* check if there is a queued write request */
	req = raw->queued_write;
	if (req == NULL) {
		/* no queued write request, use new req structure */
		req = raw3215_alloc_req();
		req->type = RAW3215_WRITE;
		req->info = raw;
		raw->queued_write = req;
	} else {
		raw->written -= req->len;
	}

	ccw = req->ccws;
	req->start = (raw->head - raw->count + raw->written) &
		     (RAW3215_BUFFER_SIZE - 1);
	/*
	 * now we have to count newlines. We can at max accept
	 * RAW3215_MAX_NEWLINE newlines in a single ssch due to
	 * a restriction in VM
	 */
	lines = 0;
	ix = req->start;
	while (lines < RAW3215_MAX_NEWLINE && ix != raw->head) {
		if (raw->buffer[ix] == 0x15)
			lines++;
		ix = (ix + 1) & (RAW3215_BUFFER_SIZE - 1);
	}
	len = ((ix - 1 - req->start) & (RAW3215_BUFFER_SIZE - 1)) + 1;
	if (len > RAW3215_MAX_BYTES)
		len = RAW3215_MAX_BYTES;
	req->len = len;
	raw->written += len;

	/* set the indication if we should try to enlarge this request */
	req->delayable = (ix == raw->head) && (len < RAW3215_MIN_WRITE);

	ix = req->start;
	while (len > 0) {
		if (ccw > req->ccws)
			ccw[-1].flags |= 0x40; /* use command chaining */
		ccw->cmd_code = 0x01; /* write, auto carrier return */
		ccw->flags = 0x20;    /* ignore incorrect length ind.  */
		ccw->cda =
			(__u32) __pa(raw->buffer + ix);
		count = len;
		if (ix + count > RAW3215_BUFFER_SIZE)
			count = RAW3215_BUFFER_SIZE - ix;
		ccw->count = count;
		len -= count;
		ix = (ix + count) & (RAW3215_BUFFER_SIZE - 1);
		ccw++;
	}
	/*
	 * Add a NOP to the channel program. 3215 devices are purely
	 * emulated and its much better to avoid the channel end
	 * interrupt in this case.
	 */
	if (ccw > req->ccws)
		ccw[-1].flags |= 0x40; /* use command chaining */
	ccw->cmd_code = 0x03; /* NOP */
	ccw->flags = 0;
	ccw->cda = 0;
	ccw->count = 1;
}