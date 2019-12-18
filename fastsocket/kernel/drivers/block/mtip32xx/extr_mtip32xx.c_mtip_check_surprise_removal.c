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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 

__attribute__((used)) static bool mtip_check_surprise_removal(struct pci_dev *pdev)
{
	u16 vendor_id = 0;

       /* Read the vendorID from the configuration space */
	pci_read_config_word(pdev, 0x00, &vendor_id);
	if (vendor_id == 0xFFFF)
		return true; /* device removed */

	return false; /* device present */
}