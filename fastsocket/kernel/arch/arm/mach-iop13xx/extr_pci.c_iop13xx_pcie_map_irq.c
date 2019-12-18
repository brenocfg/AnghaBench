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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ATUE_INTA ; 
 int ATUE_INTB ; 
 int ATUE_INTC ; 
 int ATUE_INTD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
iop13xx_pcie_map_irq(struct pci_dev *dev, u8 idsel, u8 pin)
{
	WARN_ON(idsel != 0);

	switch (pin) {
	case 1: return ATUE_INTA;
	case 2: return ATUE_INTB;
	case 3: return ATUE_INTC;
	case 4: return ATUE_INTD;
	default: return -1;
	}
}