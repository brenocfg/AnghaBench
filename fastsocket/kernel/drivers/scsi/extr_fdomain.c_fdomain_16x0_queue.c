#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phase; scalar_t__ sent_command; scalar_t__ have_data_in; scalar_t__ Message; scalar_t__ Status; scalar_t__ buffers_residual; TYPE_2__* buffer; scalar_t__ this_residual; int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__ SCp; scalar_t__ cmnd; int /*<<< orphan*/  target; } ;
struct TYPE_5__ {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ Interrupt_Cntl ; 
 int PARITY_MASK ; 
 scalar_t__ SCSI_Cntl ; 
 scalar_t__ SCSI_Data_NoACK ; 
 scalar_t__ TMC_Cntl ; 
 int adapter_mask ; 
 struct scsi_cmnd* current_SC ; 
 int /*<<< orphan*/  fdomain_make_bus_idle () ; 
 int /*<<< orphan*/  in_arbitration ; 
 scalar_t__ in_command ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ port_base ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 TYPE_2__* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_2__*) ; 

__attribute__((used)) static int fdomain_16x0_queue(struct scsi_cmnd *SCpnt,
		void (*done)(struct scsi_cmnd *))
{
   if (in_command) {
      panic( "scsi: <fdomain> fdomain_16x0_queue() NOT REENTRANT!\n" );
   }
#if EVERY_ACCESS
   printk( "queue: target = %d cmnd = 0x%02x pieces = %d size = %u\n",
	   SCpnt->target,
	   *(unsigned char *)SCpnt->cmnd,
	   scsi_sg_count(SCpnt),
	   scsi_bufflen(SCpnt));
#endif

   fdomain_make_bus_idle();

   current_SC            = SCpnt; /* Save this for the done function */
   current_SC->scsi_done = done;

   /* Initialize static data */

   if (scsi_sg_count(current_SC)) {
	   current_SC->SCp.buffer = scsi_sglist(current_SC);
	   current_SC->SCp.ptr = sg_virt(current_SC->SCp.buffer);
	   current_SC->SCp.this_residual    = current_SC->SCp.buffer->length;
	   current_SC->SCp.buffers_residual = scsi_sg_count(current_SC) - 1;
   } else {
	   current_SC->SCp.ptr              = NULL;
	   current_SC->SCp.this_residual    = 0;
	   current_SC->SCp.buffer           = NULL;
	   current_SC->SCp.buffers_residual = 0;
   }

   current_SC->SCp.Status              = 0;
   current_SC->SCp.Message             = 0;
   current_SC->SCp.have_data_in        = 0;
   current_SC->SCp.sent_command        = 0;
   current_SC->SCp.phase               = in_arbitration;

   /* Start arbitration */
   outb(0x00, port_base + Interrupt_Cntl);
   outb(0x00, port_base + SCSI_Cntl);              /* Disable data drivers */
   outb(adapter_mask, port_base + SCSI_Data_NoACK); /* Set our id bit */
   ++in_command;
   outb(0x20, port_base + Interrupt_Cntl);
   outb(0x14 | PARITY_MASK, port_base + TMC_Cntl); /* Start arbitration */

   return 0;
}