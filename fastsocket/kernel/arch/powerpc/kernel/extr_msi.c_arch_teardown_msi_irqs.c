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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown_msi_irqs ) (struct pci_dev*) ;} ;

/* Variables and functions */
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

void arch_teardown_msi_irqs(struct pci_dev *dev)
{
	ppc_md.teardown_msi_irqs(dev);
}