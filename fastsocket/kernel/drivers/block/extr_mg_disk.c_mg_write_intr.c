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
typedef  int u32 ;
struct request {int /*<<< orphan*/  buffer; } ;
struct mg_host {void (* mg_do_intr ) (struct mg_host*) ;int /*<<< orphan*/  breq; scalar_t__ dev_base; int /*<<< orphan*/  timer; struct request* req; } ;

/* Variables and functions */
 int ATA_BUSY ; 
 int ATA_DRQ ; 
 int HZ ; 
 int /*<<< orphan*/  MG_CMD_WR_CONF ; 
 int /*<<< orphan*/  MG_DBG (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MG_READY_OK (int) ; 
 scalar_t__ MG_REG_COMMAND ; 
 scalar_t__ MG_REG_STATUS ; 
 int /*<<< orphan*/  MG_SECTOR_SIZE ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int inb (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mg_bad_rw_intr (struct mg_host*) ; 
 int /*<<< orphan*/  mg_dump_status (char*,int,struct mg_host*) ; 
 int mg_end_request (struct mg_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_write_one (struct mg_host*,struct request*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mg_write_intr(struct mg_host *host)
{
	struct request *req = host->req;
	u32 i;
	bool rem;

	/* check status */
	do {
		i = inb((unsigned long)host->dev_base + MG_REG_STATUS);
		if (i & ATA_BUSY)
			break;
		if (!MG_READY_OK(i))
			break;
		if ((blk_rq_sectors(req) <= 1) || (i & ATA_DRQ))
			goto ok_to_write;
	} while (0);
	mg_dump_status("mg_write_intr", i, host);
	mg_bad_rw_intr(host);
	mg_request(host->breq);
	return;

ok_to_write:
	if ((rem = mg_end_request(host, 0, MG_SECTOR_SIZE))) {
		/* write 1 sector and set handler if remains */
		mg_write_one(host, req);
		MG_DBG("sector %ld, remaining=%ld, buffer=0x%p\n",
		       blk_rq_pos(req), blk_rq_sectors(req), req->buffer);
		host->mg_do_intr = mg_write_intr;
		mod_timer(&host->timer, jiffies + 3 * HZ);
	}

	/* send write confirm */
	outb(MG_CMD_WR_CONF, (unsigned long)host->dev_base + MG_REG_COMMAND);

	if (!rem)
		mg_request(host->breq);
}