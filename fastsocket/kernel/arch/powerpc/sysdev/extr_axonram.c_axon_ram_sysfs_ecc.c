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
struct TYPE_2__ {struct axon_ram_bank* platform_data; } ;
struct of_device {TYPE_1__ dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct axon_ram_bank {int /*<<< orphan*/  ecc_counter; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct of_device* to_of_device (struct device*) ; 

__attribute__((used)) static ssize_t
axon_ram_sysfs_ecc(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct of_device *device = to_of_device(dev);
	struct axon_ram_bank *bank = device->dev.platform_data;

	BUG_ON(!bank);

	return sprintf(buf, "%ld\n", bank->ecc_counter);
}