#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  serial_number; int /*<<< orphan*/ * host_scribble; TYPE_1__* device; } ;
struct hostdata {scalar_t__* cp_stat; int /*<<< orphan*/  board_name; TYPE_2__* cp; } ;
struct Scsi_Host {unsigned int can_queue; scalar_t__ io_port; scalar_t__ hostdata; } ;
struct TYPE_4__ {struct scsi_cmnd* SCpnt; } ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 scalar_t__ ABORTING ; 
 int DID_ABORT ; 
 int FAILED ; 
 scalar_t__ FREE ; 
 scalar_t__ IN_RESET ; 
 scalar_t__ IN_USE ; 
 int IRQ_ASSERTED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ LOCKED ; 
 int /*<<< orphan*/  MAXLOOP ; 
 scalar_t__ READY ; 
 scalar_t__ REG_AUX_STATUS ; 
 int SUCCESS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  unmap_dma (unsigned int,struct hostdata*) ; 
 scalar_t__ wait_on_busy (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eata2x_eh_abort(struct scsi_cmnd *SCarg)
{
	struct Scsi_Host *shost = SCarg->device->host;
	struct hostdata *ha = (struct hostdata *)shost->hostdata;
	unsigned int i;

	if (SCarg->host_scribble == NULL) {
		scmd_printk(KERN_INFO, SCarg,
			"abort, pid %ld inactive.\n", SCarg->serial_number);
		return SUCCESS;
	}

	i = *(unsigned int *)SCarg->host_scribble;
	scmd_printk(KERN_WARNING, SCarg,
		"abort, mbox %d, pid %ld.\n", i, SCarg->serial_number);

	if (i >= shost->can_queue)
		panic("%s: abort, invalid SCarg->host_scribble.\n", ha->board_name);

	if (wait_on_busy(shost->io_port, MAXLOOP)) {
		printk("%s: abort, timeout error.\n", ha->board_name);
		return FAILED;
	}

	if (ha->cp_stat[i] == FREE) {
		printk("%s: abort, mbox %d is free.\n", ha->board_name, i);
		return SUCCESS;
	}

	if (ha->cp_stat[i] == IN_USE) {
		printk("%s: abort, mbox %d is in use.\n", ha->board_name, i);

		if (SCarg != ha->cp[i].SCpnt)
			panic("%s: abort, mbox %d, SCarg %p, cp SCpnt %p.\n",
			      ha->board_name, i, SCarg, ha->cp[i].SCpnt);

		if (inb(shost->io_port + REG_AUX_STATUS) & IRQ_ASSERTED)
			printk("%s: abort, mbox %d, interrupt pending.\n",
			       ha->board_name, i);

		return FAILED;
	}

	if (ha->cp_stat[i] == IN_RESET) {
		printk("%s: abort, mbox %d is in reset.\n", ha->board_name, i);
		return FAILED;
	}

	if (ha->cp_stat[i] == LOCKED) {
		printk("%s: abort, mbox %d is locked.\n", ha->board_name, i);
		return SUCCESS;
	}

	if (ha->cp_stat[i] == READY || ha->cp_stat[i] == ABORTING) {
		unmap_dma(i, ha);
		SCarg->result = DID_ABORT << 16;
		SCarg->host_scribble = NULL;
		ha->cp_stat[i] = FREE;
		printk("%s, abort, mbox %d ready, DID_ABORT, pid %ld done.\n",
		       ha->board_name, i, SCarg->serial_number);
		SCarg->scsi_done(SCarg);
		return SUCCESS;
	}

	panic("%s: abort, mbox %d, invalid cp_stat.\n", ha->board_name, i);
}