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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int get_base_addr (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mmcfg_virt_addr ; 
 int mmio_config_readb (int /*<<< orphan*/ ) ; 
 int mmio_config_readl (int /*<<< orphan*/ ) ; 
 int mmio_config_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_config_lock ; 
 int /*<<< orphan*/  pci_exp_set_dev_base (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci_mmcfg_read(unsigned int seg, unsigned int bus,
			  unsigned int devfn, int reg, int len, u32 *value)
{
	unsigned long flags;
	u32 base;

	if ((bus > 255) || (devfn > 255) || (reg > 4095)) {
err:		*value = -1;
		return -EINVAL;
	}

	base = get_base_addr(seg, bus, devfn);
	if (!base)
		goto err;

	spin_lock_irqsave(&pci_config_lock, flags);

	pci_exp_set_dev_base(base, bus, devfn);

	switch (len) {
	case 1:
		*value = mmio_config_readb(mmcfg_virt_addr + reg);
		break;
	case 2:
		*value = mmio_config_readw(mmcfg_virt_addr + reg);
		break;
	case 4:
		*value = mmio_config_readl(mmcfg_virt_addr + reg);
		break;
	}
	spin_unlock_irqrestore(&pci_config_lock, flags);

	return 0;
}