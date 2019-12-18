#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {unsigned char* host_scribble; void (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  serial_number; int /*<<< orphan*/  request; TYPE_3__* device; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct mscp {unsigned int cpp_index; int /*<<< orphan*/  cp_dma_addr; int /*<<< orphan*/  cdb; int /*<<< orphan*/  cdb_len; struct scsi_cmnd* SCpnt; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; int /*<<< orphan*/  opcode; } ;
struct hostdata {unsigned int board_number; } ;
struct TYPE_8__ {int last_cp_used; scalar_t__* cp_stat; struct mscp* cp; } ;
struct TYPE_7__ {int queue_depth; int /*<<< orphan*/  type; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; TYPE_1__* host; } ;
struct TYPE_6__ {unsigned int can_queue; scalar_t__ io_port; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN (unsigned int) ; 
 int /*<<< orphan*/  CMD_OGM_INTR ; 
 scalar_t__ CP_TAIL_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FREE ; 
 int /*<<< orphan*/  H2DEV (int /*<<< orphan*/ ) ; 
 TYPE_4__* HD (unsigned int) ; 
 scalar_t__ IN_USE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MAXLOOP ; 
 int /*<<< orphan*/  OP_SCSI ; 
 scalar_t__ READY ; 
 scalar_t__ REG_LCL_INTR ; 
 scalar_t__ REG_OGM ; 
 scalar_t__ TLDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (int /*<<< orphan*/ ) ; 
 scalar_t__ do_trace ; 
 int /*<<< orphan*/  flush_dev (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ linked_comm ; 
 int /*<<< orphan*/  map_dma (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mscp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_to_dev_dir (unsigned int,unsigned int) ; 
 TYPE_2__** sh ; 
 int /*<<< orphan*/  unmap_dma (unsigned int,unsigned int) ; 
 scalar_t__ wait_on_busy (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u14_34f_queuecommand(struct scsi_cmnd *SCpnt, void (*done)(struct scsi_cmnd *)) {
   unsigned int i, j, k;
   struct mscp *cpp;

   /* j is the board number */
   j = ((struct hostdata *) SCpnt->device->host->hostdata)->board_number;

   if (SCpnt->host_scribble)
      panic("%s: qcomm, pid %ld, SCpnt %p already active.\n",
            BN(j), SCpnt->serial_number, SCpnt);

   /* i is the mailbox number, look for the first free mailbox
      starting from last_cp_used */
   i = HD(j)->last_cp_used + 1;

   for (k = 0; k < sh[j]->can_queue; k++, i++) {

      if (i >= sh[j]->can_queue) i = 0;

      if (HD(j)->cp_stat[i] == FREE) {
         HD(j)->last_cp_used = i;
         break;
         }
      }

   if (k == sh[j]->can_queue) {
      printk("%s: qcomm, no free mailbox.\n", BN(j));
      return 1;
      }

   /* Set pointer to control packet structure */
   cpp = &HD(j)->cp[i];

   memset(cpp, 0, sizeof(struct mscp) - CP_TAIL_SIZE);
   SCpnt->scsi_done = done;
   cpp->cpp_index = i;
   SCpnt->host_scribble = (unsigned char *) &cpp->cpp_index;

   if (do_trace) printk("%s: qcomm, mbox %d, target %d.%d:%d, pid %ld.\n",
                        BN(j), i, SCpnt->device->channel, SCpnt->device->id,
                        SCpnt->device->lun, SCpnt->serial_number);

   cpp->opcode = OP_SCSI;
   cpp->channel = SCpnt->device->channel;
   cpp->target = SCpnt->device->id;
   cpp->lun = SCpnt->device->lun;
   cpp->SCpnt = SCpnt;
   cpp->cdb_len = SCpnt->cmd_len;
   memcpy(cpp->cdb, SCpnt->cmnd, SCpnt->cmd_len);

   /* Use data transfer direction SCpnt->sc_data_direction */
   scsi_to_dev_dir(i, j);

   /* Map DMA buffers and SG list */
   map_dma(i, j);

   if (linked_comm && SCpnt->device->queue_depth > 2
                                     && TLDEV(SCpnt->device->type)) {
      HD(j)->cp_stat[i] = READY;
      flush_dev(SCpnt->device, blk_rq_pos(SCpnt->request), j, FALSE);
      return 0;
      }

   if (wait_on_busy(sh[j]->io_port, MAXLOOP)) {
      unmap_dma(i, j);
      SCpnt->host_scribble = NULL;
      scmd_printk(KERN_INFO, SCpnt,
      		"qcomm, pid %ld, adapter busy.\n", SCpnt->serial_number);
      return 1;
      }

   /* Store pointer in OGM address bytes */
   outl(H2DEV(cpp->cp_dma_addr), sh[j]->io_port + REG_OGM);

   /* Issue OGM interrupt */
   outb(CMD_OGM_INTR, sh[j]->io_port + REG_LCL_INTR);

   HD(j)->cp_stat[i] = IN_USE;
   return 0;
}