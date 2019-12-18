#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct bnx2x {TYPE_1__* pdev; scalar_t__ pm_cap; int /*<<< orphan*/  wol; } ;
typedef  int pci_power_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  enable_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*) ; 
 int /*<<< orphan*/  CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int EINVAL ; 
#define  PCI_D0 129 
#define  PCI_D3hot 128 
 scalar_t__ PCI_PM_CTRL ; 
 int PCI_PM_CTRL_PME_ENABLE ; 
 int PCI_PM_CTRL_PME_STATUS ; 
 int PCI_PM_CTRL_STATE_MASK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_1__*,scalar_t__,int) ; 

int bnx2x_set_power_state(struct bnx2x *bp, pci_power_t state)
{
	u16 pmcsr;

	/* If there is no power capability, silently succeed */
	if (!bp->pm_cap) {
		BNX2X_DEV_INFO("No power capability. Breaking.\n");
		return 0;
	}

	pci_read_config_word(bp->pdev, bp->pm_cap + PCI_PM_CTRL, &pmcsr);

	switch (state) {
	case PCI_D0:
		pci_write_config_word(bp->pdev, bp->pm_cap + PCI_PM_CTRL,
				      ((pmcsr & ~PCI_PM_CTRL_STATE_MASK) |
				       PCI_PM_CTRL_PME_STATUS));

		if (pmcsr & PCI_PM_CTRL_STATE_MASK)
			/* delay required during transition out of D3hot */
			msleep(20);
		break;

	case PCI_D3hot:
		/* If there are other clients above don't
		   shut down the power */
		if (atomic_read(&bp->pdev->enable_cnt) != 1)
			return 0;
		/* Don't shut down the power for emulation and FPGA */
		if (CHIP_REV_IS_SLOW(bp))
			return 0;

		pmcsr &= ~PCI_PM_CTRL_STATE_MASK;
		pmcsr |= 3;

		if (bp->wol)
			pmcsr |= PCI_PM_CTRL_PME_ENABLE;

		pci_write_config_word(bp->pdev, bp->pm_cap + PCI_PM_CTRL,
				      pmcsr);

		/* No more memory access after this point until
		* device is brought back to D0.
		*/
		break;

	default:
		dev_err(&bp->pdev->dev, "Can't support state = %d\n", state);
		return -EINVAL;
	}
	return 0;
}