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
 int driver_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nes_create_driver_sysfs(struct pci_driver *drv)
{
	int error;
	error  = driver_create_file(&drv->driver, &driver_attr_adapter);
	error |= driver_create_file(&drv->driver, &driver_attr_eeprom_cmd);
	error |= driver_create_file(&drv->driver, &driver_attr_eeprom_data);
	error |= driver_create_file(&drv->driver, &driver_attr_flash_cmd);
	error |= driver_create_file(&drv->driver, &driver_attr_flash_data);
	error |= driver_create_file(&drv->driver, &driver_attr_nonidx_addr);
	error |= driver_create_file(&drv->driver, &driver_attr_nonidx_data);
	error |= driver_create_file(&drv->driver, &driver_attr_idx_addr);
	error |= driver_create_file(&drv->driver, &driver_attr_idx_data);
	error |= driver_create_file(&drv->driver, &driver_attr_wqm_quanta);
	return error;
}