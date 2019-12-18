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
struct request {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int BUSY_STAT ; 
 int DRQ_STAT ; 
 int /*<<< orphan*/  HD_DATA ; 
 int /*<<< orphan*/  HD_STATUS ; 
 int /*<<< orphan*/  OK_STATUS (int) ; 
 int /*<<< orphan*/  SET_HANDLER (void (*) ()) ; 
 int /*<<< orphan*/  bad_rw_intr () ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  dump_status (char*,int) ; 
 scalar_t__ hd_end_request (int /*<<< orphan*/ ,int) ; 
 struct request* hd_req ; 
 int /*<<< orphan*/  hd_request () ; 
 scalar_t__ inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_req ; 
 int /*<<< orphan*/  outsw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_timer () ; 

__attribute__((used)) static void write_intr(void)
{
	struct request *req = hd_req;
	int i;
	int retries = 100000;

	do {
		i = (unsigned) inb_p(HD_STATUS);
		if (i & BUSY_STAT)
			continue;
		if (!OK_STATUS(i))
			break;
		if ((blk_rq_sectors(req) <= 1) || (i & DRQ_STAT))
			goto ok_to_write;
	} while (--retries > 0);
	dump_status("write_intr", i);
	bad_rw_intr();
	hd_request();
	return;

ok_to_write:
	if (hd_end_request(0, 512)) {
		SET_HANDLER(&write_intr);
		outsw(HD_DATA, req->buffer, 256);
		return;
	}

#if (HD_DELAY > 0)
	last_req = read_timer();
#endif
	hd_request();
}