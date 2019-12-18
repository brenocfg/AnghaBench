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
struct asd_ha_struct {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_bios_build ; 
 int /*<<< orphan*/  dev_attr_pcba_sn ; 
 int /*<<< orphan*/  dev_attr_revision ; 
 int /*<<< orphan*/  dev_attr_update_bios ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asd_remove_dev_attrs(struct asd_ha_struct *asd_ha)
{
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_revision);
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_bios_build);
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_pcba_sn);
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_update_bios);
}