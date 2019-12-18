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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  ide_hwif_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/ * dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ide_port_scan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_port_unregister_devices (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static ssize_t store_scan(struct device *portdev,
			  struct device_attribute *attr,
			  const char *buf, size_t n)
{
	ide_hwif_t *hwif = dev_get_drvdata(portdev);

	if (strncmp(buf, "1", n))
		return -EINVAL;

	ide_port_unregister_devices(hwif);
	ide_port_scan(hwif);

	return n;
}