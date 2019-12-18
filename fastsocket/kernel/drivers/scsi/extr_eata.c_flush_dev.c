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
struct scsi_device {TYPE_1__* host; } ;
struct scsi_cmnd {int /*<<< orphan*/  serial_number; struct scsi_device* device; } ;
struct mscp {int /*<<< orphan*/  cp_dma_addr; struct scsi_cmnd* SCpnt; } ;
struct hostdata {scalar_t__* cp_stat; struct mscp* cp; } ;
struct TYPE_2__ {unsigned int can_queue; int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 scalar_t__ ABORTING ; 
 scalar_t__ IN_USE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MAX_MAILBOXES ; 
 scalar_t__ READY ; 
 int /*<<< orphan*/  SEND_CP_DMA ; 
 scalar_t__ do_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reorder (struct hostdata*,unsigned long,unsigned int,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void flush_dev(struct scsi_device *dev, unsigned long cursec,
		      struct hostdata *ha, unsigned int ihdlr)
{
	struct scsi_cmnd *SCpnt;
	struct mscp *cpp;
	unsigned int k, n, n_ready = 0, il[MAX_MAILBOXES];

	for (k = 0; k < dev->host->can_queue; k++) {

		if (ha->cp_stat[k] != READY && ha->cp_stat[k] != IN_USE)
			continue;

		cpp = &ha->cp[k];
		SCpnt = cpp->SCpnt;

		if (SCpnt->device != dev)
			continue;

		if (ha->cp_stat[k] == IN_USE)
			return;

		il[n_ready++] = k;
	}

	if (reorder(ha, cursec, ihdlr, il, n_ready))
		n_ready = 1;

	for (n = 0; n < n_ready; n++) {
		k = il[n];
		cpp = &ha->cp[k];
		SCpnt = cpp->SCpnt;

		if (do_dma(dev->host->io_port, cpp->cp_dma_addr, SEND_CP_DMA)) {
			scmd_printk(KERN_INFO, SCpnt,
			    "%s, pid %ld, mbox %d, adapter"
			     " busy, will abort.\n",
			     (ihdlr ? "ihdlr" : "qcomm"),
			     SCpnt->serial_number, k);
			ha->cp_stat[k] = ABORTING;
			continue;
		}

		ha->cp_stat[k] = IN_USE;
	}
}