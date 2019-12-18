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
struct request {scalar_t__ buffer; TYPE_1__* rq_disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int BUSY_STAT ; 
 int DRQ_STAT ; 
 int /*<<< orphan*/  HD_DATA ; 
 int /*<<< orphan*/  HD_STATUS ; 
 int /*<<< orphan*/  OK_STATUS (int) ; 
 int /*<<< orphan*/  SET_HANDLER (void (*) ()) ; 
 int /*<<< orphan*/  bad_rw_intr () ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  dump_status (char*,int) ; 
 scalar_t__ hd_end_request (int /*<<< orphan*/ ,int) ; 
 struct request* hd_req ; 
 int /*<<< orphan*/  hd_request () ; 
 scalar_t__ inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insw (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  last_req ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_timer () ; 

__attribute__((used)) static void read_intr(void)
{
	struct request *req;
	int i, retries = 100000;

	do {
		i = (unsigned) inb_p(HD_STATUS);
		if (i & BUSY_STAT)
			continue;
		if (!OK_STATUS(i))
			break;
		if (i & DRQ_STAT)
			goto ok_to_read;
	} while (--retries > 0);
	dump_status("read_intr", i);
	bad_rw_intr();
	hd_request();
	return;

ok_to_read:
	req = hd_req;
	insw(HD_DATA, req->buffer, 256);
#ifdef DEBUG
	printk("%s: read: sector %ld, remaining = %u, buffer=%p\n",
	       req->rq_disk->disk_name, blk_rq_pos(req) + 1,
	       blk_rq_sectors(req) - 1, req->buffer+512);
#endif
	if (hd_end_request(0, 512)) {
		SET_HANDLER(&read_intr);
		return;
	}

	(void) inb_p(HD_STATUS);
#if (HD_DELAY > 0)
	last_req = read_timer();
#endif
	hd_request();
}