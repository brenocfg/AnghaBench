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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev_rh1 {int /*<<< orphan*/  pcie_mpss; } ;
struct pci_dev {scalar_t__ rh_reserved1; } ;

/* Variables and functions */

void rh_set_mpss(struct pci_dev *dev, u8 mpss)
{
	((struct pci_dev_rh1 *) dev->rh_reserved1)->pcie_mpss = mpss;
}