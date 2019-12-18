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
struct scsi_cmnd {unsigned char* host_scribble; void (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  serial_number; int /*<<< orphan*/  request; TYPE_1__* device; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct mscp {unsigned int cpp_index; int reqsen; int dispri; int hbaci; int one; int /*<<< orphan*/  cp_dma_addr; int /*<<< orphan*/  cdb; struct scsi_cmnd* SCpnt; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; int /*<<< orphan*/  sp_dma_addr; } ;
struct hostdata {int last_cp_used; scalar_t__* cp_stat; int /*<<< orphan*/  sp_dma_addr; struct mscp* cp; int /*<<< orphan*/  board_name; } ;
struct Scsi_Host {unsigned int can_queue; int /*<<< orphan*/  io_port; scalar_t__ hostdata; } ;
struct TYPE_2__ {scalar_t__ type; int queue_depth; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; struct Scsi_Host* host; } ;

/* Variables and functions */
 scalar_t__ CP_TAIL_SIZE ; 
 scalar_t__ FREE ; 
 int /*<<< orphan*/  H2DEV (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_USE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ READY ; 
 int /*<<< orphan*/  SEND_CP_DMA ; 
 scalar_t__ TLDEV (scalar_t__) ; 
 scalar_t__ TYPE_TAPE ; 
 int /*<<< orphan*/  blk_rq_pos (int /*<<< orphan*/ ) ; 
 scalar_t__ do_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ do_trace ; 
 int /*<<< orphan*/  flush_dev (TYPE_1__*,int /*<<< orphan*/ ,struct hostdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ linked_comm ; 
 int /*<<< orphan*/  map_dma (unsigned int,struct hostdata*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mscp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  scsi_to_dev_dir (unsigned int,struct hostdata*) ; 
 int /*<<< orphan*/  unmap_dma (unsigned int,struct hostdata*) ; 

__attribute__((used)) static int eata2x_queuecommand(struct scsi_cmnd *SCpnt,
			       void (*done) (struct scsi_cmnd *))
{
	struct Scsi_Host *shost = SCpnt->device->host;
	struct hostdata *ha = (struct hostdata *)shost->hostdata;
	unsigned int i, k;
	struct mscp *cpp;

	if (SCpnt->host_scribble)
		panic("%s: qcomm, pid %ld, SCpnt %p already active.\n",
		      ha->board_name, SCpnt->serial_number, SCpnt);

	/* i is the mailbox number, look for the first free mailbox
	   starting from last_cp_used */
	i = ha->last_cp_used + 1;

	for (k = 0; k < shost->can_queue; k++, i++) {
		if (i >= shost->can_queue)
			i = 0;
		if (ha->cp_stat[i] == FREE) {
			ha->last_cp_used = i;
			break;
		}
	}

	if (k == shost->can_queue) {
		printk("%s: qcomm, no free mailbox.\n", ha->board_name);
		return 1;
	}

	/* Set pointer to control packet structure */
	cpp = &ha->cp[i];

	memset(cpp, 0, sizeof(struct mscp) - CP_TAIL_SIZE);

	/* Set pointer to status packet structure, Big Endian format */
	cpp->sp_dma_addr = H2DEV(ha->sp_dma_addr);

	SCpnt->scsi_done = done;
	cpp->cpp_index = i;
	SCpnt->host_scribble = (unsigned char *)&cpp->cpp_index;

	if (do_trace)
		scmd_printk(KERN_INFO, SCpnt,
			"qcomm, mbox %d, pid %ld.\n", i, SCpnt->serial_number);

	cpp->reqsen = 1;
	cpp->dispri = 1;
#if 0
	if (SCpnt->device->type == TYPE_TAPE)
		cpp->hbaci = 1;
#endif
	cpp->one = 1;
	cpp->channel = SCpnt->device->channel;
	cpp->target = SCpnt->device->id;
	cpp->lun = SCpnt->device->lun;
	cpp->SCpnt = SCpnt;
	memcpy(cpp->cdb, SCpnt->cmnd, SCpnt->cmd_len);

	/* Use data transfer direction SCpnt->sc_data_direction */
	scsi_to_dev_dir(i, ha);

	/* Map DMA buffers and SG list */
	map_dma(i, ha);

	if (linked_comm && SCpnt->device->queue_depth > 2
	    && TLDEV(SCpnt->device->type)) {
		ha->cp_stat[i] = READY;
		flush_dev(SCpnt->device, blk_rq_pos(SCpnt->request), ha, 0);
		return 0;
	}

	/* Send control packet to the board */
	if (do_dma(shost->io_port, cpp->cp_dma_addr, SEND_CP_DMA)) {
		unmap_dma(i, ha);
		SCpnt->host_scribble = NULL;
		scmd_printk(KERN_INFO, SCpnt,
			"qcomm, pid %ld, adapter busy.\n", SCpnt->serial_number);
		return 1;
	}

	ha->cp_stat[i] = IN_USE;
	return 0;
}