#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* device; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_3__ Scsi_Cmnd ;

/* Variables and functions */
 int /*<<< orphan*/  C4_IMG ; 
 int /*<<< orphan*/  CHIP_RESET ; 
 int /*<<< orphan*/  CMD_REG ; 
 int /*<<< orphan*/  CONFIG4 ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_NOP ; 
 int /*<<< orphan*/  SCSI_RESET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  chip_init () ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rtrc (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int NCR53c406a_host_reset(Scsi_Cmnd * SCpnt)
{
	DEB(printk("NCR53c406a_reset called\n"));

	spin_lock_irq(SCpnt->device->host->host_lock);

	outb(C4_IMG, CONFIG4);	/* Select reg set 0 */
	outb(CHIP_RESET, CMD_REG);
	outb(SCSI_NOP, CMD_REG);	/* required after reset */
	outb(SCSI_RESET, CMD_REG);
	chip_init();

	rtrc(2);

	spin_unlock_irq(SCpnt->device->host->host_lock);

	return SUCCESS;
}