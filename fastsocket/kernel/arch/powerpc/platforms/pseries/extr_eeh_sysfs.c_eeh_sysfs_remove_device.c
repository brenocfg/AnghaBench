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
 int /*<<< orphan*/  dev_attr_eeh_check_count ; 
 int /*<<< orphan*/  dev_attr_eeh_config_addr ; 
 int /*<<< orphan*/  dev_attr_eeh_false_positives ; 
 int /*<<< orphan*/  dev_attr_eeh_freeze_count ; 
 int /*<<< orphan*/  dev_attr_eeh_mode ; 
 int /*<<< orphan*/  dev_attr_eeh_pe_config_addr ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void eeh_sysfs_remove_device(struct pci_dev *pdev)
{
	device_remove_file(&pdev->dev, &dev_attr_eeh_mode);
	device_remove_file(&pdev->dev, &dev_attr_eeh_config_addr);
	device_remove_file(&pdev->dev, &dev_attr_eeh_pe_config_addr);
	device_remove_file(&pdev->dev, &dev_attr_eeh_check_count);
	device_remove_file(&pdev->dev, &dev_attr_eeh_false_positives);
	device_remove_file(&pdev->dev, &dev_attr_eeh_freeze_count);
}