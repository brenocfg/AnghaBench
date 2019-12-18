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
struct TYPE_2__ {int /*<<< orphan*/  attr_group; int /*<<< orphan*/  miscdev; } ;
struct tpm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  bios_dir; TYPE_1__ vendor; int /*<<< orphan*/  list; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct tpm_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  driver_lock ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_bios_log_teardown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_remove_ppi (int /*<<< orphan*/ *) ; 

void tpm_remove_hardware(struct device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);

	if (chip == NULL) {
		dev_err(dev, "No device data found\n");
		return;
	}

	spin_lock(&driver_lock);
	list_del_rcu(&chip->list);
	spin_unlock(&driver_lock);
	synchronize_rcu();

	misc_deregister(&chip->vendor.miscdev);
	sysfs_remove_group(&dev->kobj, chip->vendor.attr_group);
	tpm_remove_ppi(&dev->kobj);
	tpm_bios_log_teardown(chip->bios_dir);

	/* write it this way to be explicit (chip->dev == dev) */
	put_device(chip->dev);
}