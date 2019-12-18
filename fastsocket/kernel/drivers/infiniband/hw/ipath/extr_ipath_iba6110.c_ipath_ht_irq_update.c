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
typedef  int u64 ;
struct pci_dev {int dummy; } ;
struct ipath_devdata {int ipath_intconfig; } ;
struct ht_irq_msg {int address_lo; scalar_t__ address_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_ht_intconfig (struct ipath_devdata*) ; 
 struct ipath_devdata* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void ipath_ht_irq_update(struct pci_dev *dev, int irq,
				struct ht_irq_msg *msg)
{
	struct ipath_devdata *dd = pci_get_drvdata(dev);
	u64 prev_intconfig = dd->ipath_intconfig;

	dd->ipath_intconfig = msg->address_lo;
	dd->ipath_intconfig |= ((u64) msg->address_hi) << 32;

	/*
	 * If the previous value of dd->ipath_intconfig is zero, we're
	 * getting configured for the first time, and must not program the
	 * intconfig register here (it will be programmed later, when the
	 * hardware is ready).  Otherwise, we should.
	 */
	if (prev_intconfig)
		ipath_ht_intconfig(dd);
}