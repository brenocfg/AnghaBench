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
typedef  scalar_t__ u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct atl1_hw {scalar_t__ hw_addr; struct atl1_adapter* back; } ;
struct atl1_adapter {struct pci_dev* pdev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_CTRL_SOFT_RST ; 
 scalar_t__ REG_IDLE_STATUS ; 
 scalar_t__ REG_MASTER_CTRL ; 
 scalar_t__ REG_PHY_ENABLE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ netif_msg_hw (struct atl1_adapter*) ; 

__attribute__((used)) static s32 atl1_reset_hw(struct atl1_hw *hw)
{
	struct pci_dev *pdev = hw->back->pdev;
	struct atl1_adapter *adapter = hw->back;
	u32 icr;
	int i;

	/*
	 * Clear Interrupt mask to stop board from generating
	 * interrupts & Clear any pending interrupt events
	 */
	/*
	 * iowrite32(0, hw->hw_addr + REG_IMR);
	 * iowrite32(0xffffffff, hw->hw_addr + REG_ISR);
	 */

	/*
	 * Issue Soft Reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	iowrite32(MASTER_CTRL_SOFT_RST, hw->hw_addr + REG_MASTER_CTRL);
	ioread32(hw->hw_addr + REG_MASTER_CTRL);

	iowrite16(1, hw->hw_addr + REG_PHY_ENABLE);
	ioread16(hw->hw_addr + REG_PHY_ENABLE);

	/* delay about 1ms */
	msleep(1);

	/* Wait at least 10ms for All module to be Idle */
	for (i = 0; i < 10; i++) {
		icr = ioread32(hw->hw_addr + REG_IDLE_STATUS);
		if (!icr)
			break;
		/* delay 1 ms */
		msleep(1);
		/* FIXME: still the right way to do this? */
		cpu_relax();
	}

	if (icr) {
		if (netif_msg_hw(adapter))
			dev_dbg(&pdev->dev, "ICR = 0x%x\n", icr);
		return icr;
	}

	return 0;
}