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
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asd_create_dev_attrs(struct asd_ha_struct *asd_ha)
{
	int err;

	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_revision);
	if (err)
		return err;

	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_bios_build);
	if (err)
		goto err_rev;

	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_pcba_sn);
	if (err)
		goto err_biosb;
	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_update_bios);
	if (err)
		goto err_update_bios;

	return 0;

err_update_bios:
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_pcba_sn);
err_biosb:
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_bios_build);
err_rev:
	device_remove_file(&asd_ha->pcidev->dev, &dev_attr_revision);
	return err;
}