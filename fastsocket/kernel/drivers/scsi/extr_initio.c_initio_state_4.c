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
struct scsi_ctrl_blk {int flags; scalar_t__ buflen; int next_state; void* hastat; } ;
struct initio_host {int phase; int jsstatus0; scalar_t__ addr; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
#define  DATA_IN 132 
#define  DATA_OUT 131 
 void* HOST_DO_DU ; 
#define  MSG_IN 130 
 int /*<<< orphan*/  MSG_NOP ; 
#define  MSG_OUT 129 
 int SCF_DIR ; 
 int SCF_NO_XF ; 
#define  STATUS_IN 128 
 int /*<<< orphan*/  TSC_XF_FIFO_OUT ; 
 int TSS_PAR_ERROR ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SFifo ; 
 int initio_bad_seq (struct initio_host*) ; 
 int initio_msgin (struct initio_host*) ; 
 int initio_msgout_ide (struct initio_host*) ; 
 int initio_status_msg (struct initio_host*) ; 
 int initio_xfer_data_in (struct initio_host*) ; 
 int initio_xfer_data_out (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int wait_tulip (struct initio_host*) ; 

__attribute__((used)) static int initio_state_4(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;

#if DEBUG_STATE
	printk("-s4-");
#endif
	if ((scb->flags & SCF_DIR) == SCF_NO_XF) {
		return 6;	/* Go to state 6 (After data) */
	}
	for (;;) {
		if (scb->buflen == 0)
			return 6;

		switch (host->phase) {

		case STATUS_IN:	/* Status phase                 */
			if ((scb->flags & SCF_DIR) != 0)	/* if direction bit set then report data underrun */
				scb->hastat = HOST_DO_DU;
			if ((initio_status_msg(host)) == -1)
				return -1;
			break;

		case MSG_IN:	/* Message in phase             */
			scb->next_state = 0x4;
			if (initio_msgin(host) == -1)
				return -1;
			break;

		case MSG_OUT:	/* Message out phase            */
			if (host->jsstatus0 & TSS_PAR_ERROR) {
				scb->buflen = 0;
				scb->hastat = HOST_DO_DU;
				if (initio_msgout_ide(host) == -1)
					return -1;
				return 6;
			} else {
				outb(MSG_NOP, host->addr + TUL_SFifo);		/* msg nop */
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				if (wait_tulip(host) == -1)
					return -1;
			}
			break;

		case DATA_IN:	/* Data in phase                */
			return initio_xfer_data_in(host);

		case DATA_OUT:	/* Data out phase               */
			return initio_xfer_data_out(host);

		default:
			return initio_bad_seq(host);
		}
	}
}