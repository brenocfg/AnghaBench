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
typedef  int u8 ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct dc390_acb {size_t AdapterIndex; int /*<<< orphan*/  ACBFlag; int /*<<< orphan*/ * pActiveDCB; scalar_t__ last_reset; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;

/* Variables and functions */
 int CLEAR_FIFO_CMD ; 
 int /*<<< orphan*/  CtrlReg1 ; 
 int DC390_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC390_write8 (int /*<<< orphan*/ ,int) ; 
 int DIS_INT_ON_SCSI_RST ; 
 size_t EE_DELAY ; 
 int HZ ; 
 int /*<<< orphan*/  INT_Status ; 
 int /*<<< orphan*/  RESET_DEV ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ScsiCmd ; 
 int /*<<< orphan*/  dc390_DoingSRB_Done (struct dc390_acb*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  dc390_ResetDevParam (struct dc390_acb*) ; 
 int /*<<< orphan*/  dc390_ResetSCSIBus (struct dc390_acb*) ; 
 int** dc390_eepromBuf ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DC390_bus_reset (struct scsi_cmnd *cmd)
{
	struct dc390_acb*    pACB = (struct dc390_acb*) cmd->device->host->hostdata;
	u8   bval;

	spin_lock_irq(cmd->device->host->host_lock);

	bval = DC390_read8(CtrlReg1) | DIS_INT_ON_SCSI_RST;
	DC390_write8(CtrlReg1, bval);	/* disable IRQ on bus reset */

	pACB->ACBFlag |= RESET_DEV;
	dc390_ResetSCSIBus(pACB);

	dc390_ResetDevParam(pACB);
	mdelay(1);
	pACB->last_reset = jiffies + 3*HZ/2
		+ HZ * dc390_eepromBuf[pACB->AdapterIndex][EE_DELAY];

	DC390_write8(ScsiCmd, CLEAR_FIFO_CMD);
	DC390_read8(INT_Status);		/* Reset Pending INT */

	dc390_DoingSRB_Done(pACB, cmd);

	pACB->pActiveDCB = NULL;
	pACB->ACBFlag = 0;

	bval = DC390_read8(CtrlReg1) & ~DIS_INT_ON_SCSI_RST;
	DC390_write8(CtrlReg1, bval);	/* re-enable interrupt */

	spin_unlock_irq(cmd->device->host->host_lock);

	return SUCCESS;
}