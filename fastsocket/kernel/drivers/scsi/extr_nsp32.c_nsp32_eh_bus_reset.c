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
struct scsi_cmnd {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  nsp32_hw_data ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {unsigned int io_port; int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_CONTROL ; 
 int /*<<< orphan*/  IRQ_CONTROL_ALL_IRQ_MASK ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  NSP32_DEBUG_BUSRESET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_do_bus_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsp32_eh_bus_reset(struct scsi_cmnd *SCpnt)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	unsigned int   base = SCpnt->device->host->io_port;

	spin_lock_irq(SCpnt->device->host->host_lock);

	nsp32_msg(KERN_INFO, "Bus Reset");	
	nsp32_dbg(NSP32_DEBUG_BUSRESET, "SCpnt=0x%x", SCpnt);

	nsp32_write2(base, IRQ_CONTROL, IRQ_CONTROL_ALL_IRQ_MASK);
	nsp32_do_bus_reset(data);
	nsp32_write2(base, IRQ_CONTROL, 0);

	spin_unlock_irq(SCpnt->device->host->host_lock);
	return SUCCESS;	/* SCSI bus reset is succeeded at any time. */
}