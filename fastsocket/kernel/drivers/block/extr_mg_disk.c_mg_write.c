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
struct request {int /*<<< orphan*/  buffer; TYPE_1__* rq_disk; } ;
struct mg_host {scalar_t__ dev_base; } ;
struct TYPE_2__ {struct mg_host* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DRQ ; 
 int /*<<< orphan*/  MG_CMD_WR ; 
 int /*<<< orphan*/  MG_CMD_WR_CONF ; 
 int /*<<< orphan*/  MG_DBG (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MG_ERR_NONE ; 
 scalar_t__ MG_REG_COMMAND ; 
 int /*<<< orphan*/  MG_SECTOR_SIZE ; 
 int /*<<< orphan*/  MG_STAT_READY ; 
 int /*<<< orphan*/  MG_TMAX_WAIT_WR_DRQ ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 unsigned int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  mg_bad_rw_intr (struct mg_host*) ; 
 scalar_t__ mg_end_request (struct mg_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mg_out (struct mg_host*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mg_wait (struct mg_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_write_one (struct mg_host*,struct request*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mg_write(struct request *req)
{
	struct mg_host *host = req->rq_disk->private_data;
	unsigned int rem = blk_rq_sectors(req);

	if (mg_out(host, blk_rq_pos(req), rem,
		   MG_CMD_WR, NULL) != MG_ERR_NONE) {
		mg_bad_rw_intr(host);
		return;
	}

	MG_DBG("requested %d sects (from %ld), buffer=0x%p\n",
	       rem, blk_rq_pos(req), req->buffer);

	if (mg_wait(host, ATA_DRQ,
		    MG_TMAX_WAIT_WR_DRQ) != MG_ERR_NONE) {
		mg_bad_rw_intr(host);
		return;
	}

	do {
		mg_write_one(host, req);

		outb(MG_CMD_WR_CONF, (unsigned long)host->dev_base +
				MG_REG_COMMAND);

		rem--;
		if (rem > 1 && mg_wait(host, ATA_DRQ,
					MG_TMAX_WAIT_WR_DRQ) != MG_ERR_NONE) {
			mg_bad_rw_intr(host);
			return;
		} else if (mg_wait(host, MG_STAT_READY,
					MG_TMAX_WAIT_WR_DRQ) != MG_ERR_NONE) {
			mg_bad_rw_intr(host);
			return;
		}
	} while (mg_end_request(host, 0, MG_SECTOR_SIZE));
}