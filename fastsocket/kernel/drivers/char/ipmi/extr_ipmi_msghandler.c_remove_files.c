#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ aux_firmware_revision_set; } ;
struct bmc_device {int /*<<< orphan*/  guid_attr; TYPE_2__* dev; scalar_t__ guid_set; int /*<<< orphan*/  aux_firmware_rev_attr; TYPE_1__ id; int /*<<< orphan*/  product_id_attr; int /*<<< orphan*/  manufacturer_id_attr; int /*<<< orphan*/  add_dev_support_attr; int /*<<< orphan*/  version_attr; int /*<<< orphan*/  firmware_rev_attr; int /*<<< orphan*/  revision_attr; int /*<<< orphan*/  provides_dev_sdrs_attr; int /*<<< orphan*/  device_id_attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_files(struct bmc_device *bmc)
{
	if (!bmc->dev)
		return;

	device_remove_file(&bmc->dev->dev,
			   &bmc->device_id_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->provides_dev_sdrs_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->revision_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->firmware_rev_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->version_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->add_dev_support_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->manufacturer_id_attr);
	device_remove_file(&bmc->dev->dev,
			   &bmc->product_id_attr);

	if (bmc->id.aux_firmware_revision_set)
		device_remove_file(&bmc->dev->dev,
				   &bmc->aux_firmware_rev_attr);
	if (bmc->guid_set)
		device_remove_file(&bmc->dev->dev,
				   &bmc->guid_attr);
}