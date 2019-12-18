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
struct pci_driver {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_adapter ; 
 int /*<<< orphan*/  driver_attr_eeprom_cmd ; 
 int /*<<< orphan*/  driver_attr_eeprom_data ; 
 int /*<<< orphan*/  driver_attr_flash_cmd ; 
 int /*<<< orphan*/  driver_attr_flash_data ; 
 int /*<<< orphan*/  driver_attr_idx_addr ; 
 int /*<<< orphan*/  driver_attr_idx_data ; 
 int /*<<< orphan*/  driver_attr_nonidx_addr ; 
 int /*<<< orphan*/  driver_attr_nonidx_data ; 
 int /*<<< orphan*/  driver_attr_wqm_quanta ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nes_remove_driver_sysfs(struct pci_driver *drv)
{
	driver_remove_file(&drv->driver, &driver_attr_adapter);
	driver_remove_file(&drv->driver, &driver_attr_eeprom_cmd);
	driver_remove_file(&drv->driver, &driver_attr_eeprom_data);
	driver_remove_file(&drv->driver, &driver_attr_flash_cmd);
	driver_remove_file(&drv->driver, &driver_attr_flash_data);
	driver_remove_file(&drv->driver, &driver_attr_nonidx_addr);
	driver_remove_file(&drv->driver, &driver_attr_nonidx_data);
	driver_remove_file(&drv->driver, &driver_attr_idx_addr);
	driver_remove_file(&drv->driver, &driver_attr_idx_data);
	driver_remove_file(&drv->driver, &driver_attr_wqm_quanta);
}