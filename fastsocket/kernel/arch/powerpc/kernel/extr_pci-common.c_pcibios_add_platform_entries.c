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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_devspec ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pcibios_add_platform_entries(struct pci_dev *pdev)
{
	return device_create_file(&pdev->dev, &dev_attr_devspec);
}