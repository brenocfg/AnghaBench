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
struct request {int dummy; } ;
struct mg_host {unsigned int error; scalar_t__ dev_base; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DRQ ; 
 int /*<<< orphan*/  ATA_NIEN ; 
 int HZ ; 
 int /*<<< orphan*/  MG_CMD_RD ; 
 int /*<<< orphan*/  MG_CMD_WR ; 
 int /*<<< orphan*/  MG_CMD_WR_CONF ; 
 unsigned int MG_ERR_NONE ; 
 int /*<<< orphan*/  MG_REG_COMMAND ; 
 int /*<<< orphan*/  MG_REG_DRV_CTRL ; 
 int /*<<< orphan*/  MG_TMAX_WAIT_WR_DRQ ; 
#define  READ 129 
#define  WRITE 128 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mg_bad_rw_intr (struct mg_host*) ; 
 unsigned int mg_out (struct mg_host*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_read_intr ; 
 int /*<<< orphan*/  mg_wait (struct mg_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_write_intr ; 
 int /*<<< orphan*/  mg_write_one (struct mg_host*,struct request*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rq_data_dir (struct request*) ; 

__attribute__((used)) static unsigned int mg_issue_req(struct request *req,
		struct mg_host *host,
		unsigned int sect_num,
		unsigned int sect_cnt)
{
	switch (rq_data_dir(req)) {
	case READ:
		if (mg_out(host, sect_num, sect_cnt, MG_CMD_RD, &mg_read_intr)
				!= MG_ERR_NONE) {
			mg_bad_rw_intr(host);
			return host->error;
		}
		break;
	case WRITE:
		/* TODO : handler */
		outb(ATA_NIEN, (unsigned long)host->dev_base + MG_REG_DRV_CTRL);
		if (mg_out(host, sect_num, sect_cnt, MG_CMD_WR, &mg_write_intr)
				!= MG_ERR_NONE) {
			mg_bad_rw_intr(host);
			return host->error;
		}
		del_timer(&host->timer);
		mg_wait(host, ATA_DRQ, MG_TMAX_WAIT_WR_DRQ);
		outb(0, (unsigned long)host->dev_base + MG_REG_DRV_CTRL);
		if (host->error) {
			mg_bad_rw_intr(host);
			return host->error;
		}
		mg_write_one(host, req);
		mod_timer(&host->timer, jiffies + 3 * HZ);
		outb(MG_CMD_WR_CONF, (unsigned long)host->dev_base +
				MG_REG_COMMAND);
		break;
	}
	return MG_ERR_NONE;
}