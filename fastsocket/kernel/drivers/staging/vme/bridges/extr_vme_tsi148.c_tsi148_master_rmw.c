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
typedef  unsigned int u32 ;
struct vme_master_resource {int number; int /*<<< orphan*/  lock; scalar_t__ kern_base; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_OFFSET_OTSAL ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTSAU ; 
 scalar_t__* TSI148_LCSR_OT ; 
 scalar_t__ TSI148_LCSR_RMWAL ; 
 scalar_t__ TSI148_LCSR_RMWAU ; 
 scalar_t__ TSI148_LCSR_RMWC ; 
 scalar_t__ TSI148_LCSR_RMWEN ; 
 scalar_t__ TSI148_LCSR_RMWS ; 
 scalar_t__ TSI148_LCSR_VMCTRL ; 
 unsigned int TSI148_LCSR_VMCTRL_RMWEN ; 
 unsigned int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_join (unsigned int,unsigned int,unsigned long long*) ; 
 int /*<<< orphan*/  reg_split (scalar_t__,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tsi148_bridge ; 
 int /*<<< orphan*/  vme_rmw ; 

unsigned int tsi148_master_rmw(struct vme_master_resource *image,
	unsigned int mask, unsigned int compare, unsigned int swap,
	loff_t offset)
{
	unsigned long long pci_addr;
	unsigned int pci_addr_high, pci_addr_low;
	u32 tmp, result;
	int i;


	/* Find the PCI address that maps to the desired VME address */
	i = image->number;

	/* Locking as we can only do one of these at a time */
	mutex_lock(&(vme_rmw));

	/* Lock image */
	spin_lock(&(image->lock));

	pci_addr_high = ioread32be(tsi148_bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAU);
	pci_addr_low = ioread32be(tsi148_bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAL);

	reg_join(pci_addr_high, pci_addr_low, &pci_addr);
	reg_split(pci_addr + offset, &pci_addr_high, &pci_addr_low);

	/* Configure registers */
	iowrite32be(mask, tsi148_bridge->base + TSI148_LCSR_RMWEN);
	iowrite32be(compare, tsi148_bridge->base + TSI148_LCSR_RMWC);
	iowrite32be(swap, tsi148_bridge->base + TSI148_LCSR_RMWS);
	iowrite32be(pci_addr_high, tsi148_bridge->base + TSI148_LCSR_RMWAU);
	iowrite32be(pci_addr_low, tsi148_bridge->base + TSI148_LCSR_RMWAL);

	/* Enable RMW */
	tmp = ioread32be(tsi148_bridge->base + TSI148_LCSR_VMCTRL);
	tmp |= TSI148_LCSR_VMCTRL_RMWEN;
	iowrite32be(tmp, tsi148_bridge->base + TSI148_LCSR_VMCTRL);

	/* Kick process off with a read to the required address. */
	result = ioread32be(image->kern_base + offset);

	/* Disable RMW */
	tmp = ioread32be(tsi148_bridge->base + TSI148_LCSR_VMCTRL);
	tmp &= ~TSI148_LCSR_VMCTRL_RMWEN;
	iowrite32be(tmp, tsi148_bridge->base + TSI148_LCSR_VMCTRL);

	spin_unlock(&(image->lock));

	mutex_unlock(&(vme_rmw));

	return result;
}