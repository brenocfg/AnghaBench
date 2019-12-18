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
struct target_control {int sconfig0; } ;
struct scsi_ctrl_blk {int dummy; } ;
struct initio_host {int jsstatus1; scalar_t__ addr; struct target_control* active_tc; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
 int TSC_FLUSH_FIFO ; 
 int TSC_SET_ACK ; 
 int TSS_CMD_PH_CMP ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SSignal ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_append_busy_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  initio_unlink_pend_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int initio_state_2(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;
	struct target_control *active_tc = host->active_tc;
#if DEBUG_STATE
	printk("-s2-");
#endif

	initio_unlink_pend_scb(host, scb);
	initio_append_busy_scb(host, scb);

	outb(active_tc->sconfig0, host->addr + TUL_SConfig);

	if (host->jsstatus1 & TSS_CMD_PH_CMP)
		return 4;

	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
	outb((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)), host->addr + TUL_SSignal);
	/* Into before CDB xfer */
	return 3;
}