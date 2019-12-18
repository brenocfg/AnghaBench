#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tg3_ocir {scalar_t__ src_data_length; scalar_t__ src_hdr_length; } ;
struct tg3 {int /*<<< orphan*/ * hwmon_dev; struct pci_dev* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int TG3_SD_NUM_RECS ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * hwmon_device_register (TYPE_1__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_group ; 
 int /*<<< orphan*/  tg3_sd_scan_scratchpad (struct tg3*,struct tg3_ocir*) ; 

__attribute__((used)) static void tg3_hwmon_open(struct tg3 *tp)
{
	int i, err;
	u32 size = 0;
	struct pci_dev *pdev = tp->pdev;
	struct tg3_ocir ocirs[TG3_SD_NUM_RECS];

	tg3_sd_scan_scratchpad(tp, ocirs);

	for (i = 0; i < TG3_SD_NUM_RECS; i++) {
		if (!ocirs[i].src_data_length)
			continue;

		size += ocirs[i].src_hdr_length;
		size += ocirs[i].src_data_length;
	}

	if (!size)
		return;

	/* Register hwmon sysfs hooks */
	err = sysfs_create_group(&pdev->dev.kobj, &tg3_group);
	if (err) {
		dev_err(&pdev->dev, "Cannot create sysfs group, aborting\n");
		return;
	}

	tp->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(tp->hwmon_dev)) {
		tp->hwmon_dev = NULL;
		dev_err(&pdev->dev, "Cannot register hwmon device, aborting\n");
		sysfs_remove_group(&pdev->dev.kobj, &tg3_group);
	}
}