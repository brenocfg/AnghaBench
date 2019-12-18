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
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int io_port; int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SYM53C500_int_host_reset (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
SYM53C500_host_reset(struct scsi_cmnd *SCpnt)
{
	int port_base = SCpnt->device->host->io_port;

	DEB(printk("SYM53C500_host_reset called\n"));
	spin_lock_irq(SCpnt->device->host->host_lock);
	SYM53C500_int_host_reset(port_base);
	spin_unlock_irq(SCpnt->device->host->host_lock);

	return SUCCESS;
}