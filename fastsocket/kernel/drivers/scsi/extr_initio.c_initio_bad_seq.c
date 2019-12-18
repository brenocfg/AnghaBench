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
struct scsi_ctrl_blk {scalar_t__ tastat; int /*<<< orphan*/  hastat; } ;
struct initio_host {struct scsi_ctrl_blk* active; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_BAD_PHAS ; 
 int /*<<< orphan*/  initio_append_done_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int initio_post_scsi_rst (struct initio_host*) ; 
 int /*<<< orphan*/  initio_reset_scsi (struct initio_host*,int) ; 
 int /*<<< orphan*/  initio_stop_bm (struct initio_host*) ; 
 int /*<<< orphan*/  initio_unlink_busy_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int initio_bad_seq(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb;

	printk("initio_bad_seg c=%d\n", host->index);

	if ((scb = host->active) != NULL) {
		initio_unlink_busy_scb(host, scb);
		scb->hastat = HOST_BAD_PHAS;
		scb->tastat = 0;
		initio_append_done_scb(host, scb);
	}
	initio_stop_bm(host);
	initio_reset_scsi(host, 8);	/* 7/29/98 */
	return initio_post_scsi_rst(host);
}