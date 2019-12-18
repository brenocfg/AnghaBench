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
struct device {int /*<<< orphan*/  kobj; } ;
struct ath5k_hw {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 int /*<<< orphan*/  ath5k_attribute_group_ani ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ath5k_sysfs_register(struct ath5k_hw *ah)
{
	struct device *dev = ah->dev;
	int err;

	err = sysfs_create_group(&dev->kobj, &ath5k_attribute_group_ani);
	if (err) {
		ATH5K_ERR(ah, "failed to create sysfs group\n");
		return err;
	}

	return 0;
}