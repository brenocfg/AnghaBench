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
struct pci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ pci_reset_function (struct pci_dev*) ; 
 scalar_t__ strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t reset_store(struct device *dev,
			   struct device_attribute *attr, const char *buf,
			   size_t count)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	unsigned long val;
	ssize_t result = strict_strtoul(buf, 0, &val);

	if (result < 0)
		return result;

	if (val != 1)
		return -EINVAL;

	result = pci_reset_function(pdev);
	if (result < 0)
		return result;

	return count;
}