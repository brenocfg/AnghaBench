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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_EXCLUSIVE ; 
 int __pci_request_region (struct pci_dev*,int,char const*,int /*<<< orphan*/ ) ; 

int pci_request_region_exclusive(struct pci_dev *pdev, int bar, const char *res_name)
{
	return __pci_request_region(pdev, bar, res_name, IORESOURCE_EXCLUSIVE);
}