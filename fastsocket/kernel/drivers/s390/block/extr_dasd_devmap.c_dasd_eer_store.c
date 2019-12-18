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
struct dasd_devmap {int /*<<< orphan*/  device; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 int PTR_ERR (struct dasd_devmap*) ; 
 struct dasd_devmap* dasd_devmap_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eer_disable (int /*<<< orphan*/ ) ; 
 int dasd_eer_enable (int /*<<< orphan*/ ) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_eer_store(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct dasd_devmap *devmap;
	int val, rc;
	char *endp;

	devmap = dasd_devmap_from_cdev(to_ccwdev(dev));
	if (IS_ERR(devmap))
		return PTR_ERR(devmap);
	if (!devmap->device)
		return -ENODEV;

	val = simple_strtoul(buf, &endp, 0);
	if (((endp + 1) < (buf + count)) || (val > 1))
		return -EINVAL;

	if (val) {
		rc = dasd_eer_enable(devmap->device);
		if (rc)
			return rc;
	} else
		dasd_eer_disable(devmap->device);
	return count;
}