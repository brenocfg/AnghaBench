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
struct bmc_device {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct bmc_device* dev_get_drvdata (struct device*) ; 
 int ipmi_version_major (int /*<<< orphan*/ *) ; 
 int ipmi_version_minor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static ssize_t ipmi_version_show(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct bmc_device *bmc = dev_get_drvdata(dev);

	return snprintf(buf, 20, "%u.%u\n",
			ipmi_version_major(&bmc->id),
			ipmi_version_minor(&bmc->id));
}