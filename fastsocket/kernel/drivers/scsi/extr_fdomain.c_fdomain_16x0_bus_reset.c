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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int PARITY_MASK ; 
 scalar_t__ SCSI_Cntl ; 
 scalar_t__ SCSI_Mode_Cntl ; 
 int SUCCESS ; 
 scalar_t__ TMC_Cntl ; 
 int /*<<< orphan*/  do_pause (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__ port_base ; 

int fdomain_16x0_bus_reset(struct scsi_cmnd *SCpnt)
{
   unsigned long flags;

   local_irq_save(flags);

   outb(1, port_base + SCSI_Cntl);
   do_pause( 2 );
   outb(0, port_base + SCSI_Cntl);
   do_pause( 115 );
   outb(0, port_base + SCSI_Mode_Cntl);
   outb(PARITY_MASK, port_base + TMC_Cntl);

   local_irq_restore(flags);
   return SUCCESS;
}