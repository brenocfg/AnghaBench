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
typedef  int u16 ;
struct pci_dev {int current_state; TYPE_1__* bus; int /*<<< orphan*/  dev; scalar_t__ pm_cap; int /*<<< orphan*/  d2_support; int /*<<< orphan*/  d1_support; } ;
typedef  int pci_power_t ;
struct TYPE_2__ {scalar_t__ self; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  PCI_D0 133 
#define  PCI_D1 132 
#define  PCI_D2 131 
#define  PCI_D3cold 130 
#define  PCI_D3hot 129 
 scalar_t__ PCI_PM_CTRL ; 
 int PCI_PM_CTRL_NO_SOFT_RESET ; 
 int PCI_PM_CTRL_STATE_MASK ; 
 int /*<<< orphan*/  PCI_PM_D2_DELAY ; 
#define  PCI_UNKNOWN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pm_d3_delay ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_restore_bars (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pcie_aspm_pm_state_change (scalar_t__) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_raw_set_power_state(struct pci_dev *dev, pci_power_t state)
{
	u16 pmcsr;
	bool need_restore = false;

	/* Check if we're already there */
	if (dev->current_state == state)
		return 0;

	if (!dev->pm_cap)
		return -EIO;

	if (state < PCI_D0 || state > PCI_D3hot)
		return -EINVAL;

	/* Validate current state:
	 * Can enter D0 from any state, but if we can only go deeper 
	 * to sleep if we're already in a low power state
	 */
	if (state != PCI_D0 && dev->current_state <= PCI_D3cold
	    && dev->current_state > state) {
		dev_err(&dev->dev, "invalid power transition "
			"(from state %d to %d)\n", dev->current_state, state);
		return -EINVAL;
	}

	/* check if this device supports the desired state */
	if ((state == PCI_D1 && !dev->d1_support)
	   || (state == PCI_D2 && !dev->d2_support))
		return -EIO;

	pci_read_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);

	/* If we're (effectively) in D3, force entire word to 0.
	 * This doesn't affect PME_Status, disables PME_En, and
	 * sets PowerState to 0.
	 */
	switch (dev->current_state) {
	case PCI_D0:
	case PCI_D1:
	case PCI_D2:
		pmcsr &= ~PCI_PM_CTRL_STATE_MASK;
		pmcsr |= state;
		break;
	case PCI_D3hot:
	case PCI_D3cold:
	case PCI_UNKNOWN: /* Boot-up */
		if ((pmcsr & PCI_PM_CTRL_STATE_MASK) == PCI_D3hot
		 && !(pmcsr & PCI_PM_CTRL_NO_SOFT_RESET))
			need_restore = true;
		/* Fall-through: force to D0 */
	default:
		pmcsr = 0;
		break;
	}

	/* enter specified state */
	pci_write_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pmcsr);

	/* Mandatory power management transition delays */
	/* see PCI PM 1.1 5.6.1 table 18 */
	if (state == PCI_D3hot || dev->current_state == PCI_D3hot)
		msleep(pci_pm_d3_delay);
	else if (state == PCI_D2 || dev->current_state == PCI_D2)
		udelay(PCI_PM_D2_DELAY);

	pci_read_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	dev->current_state = (pmcsr & PCI_PM_CTRL_STATE_MASK);
	if (dev->current_state != state && printk_ratelimit())
		dev_info(&dev->dev, "Refused to change power state, "
			"currently in D%d\n", dev->current_state);

	/* According to section 5.4.1 of the "PCI BUS POWER MANAGEMENT
	 * INTERFACE SPECIFICATION, REV. 1.2", a device transitioning
	 * from D3hot to D0 _may_ perform an internal reset, thereby
	 * going to "D0 Uninitialized" rather than "D0 Initialized".
	 * For example, at least some versions of the 3c905B and the
	 * 3c556B exhibit this behaviour.
	 *
	 * At least some laptop BIOSen (e.g. the Thinkpad T21) leave
	 * devices in a D3hot state at boot.  Consequently, we need to
	 * restore at least the BARs so that the device will be
	 * accessible to its driver.
	 */
	if (need_restore)
		pci_restore_bars(dev);

	if (dev->bus->self)
		pcie_aspm_pm_state_change(dev->bus->self);

	return 0;
}