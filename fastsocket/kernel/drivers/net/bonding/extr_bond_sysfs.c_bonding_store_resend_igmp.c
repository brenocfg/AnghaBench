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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int resend_igmp; } ;
struct bonding {TYPE_1__ params; TYPE_2__* dev; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int*) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_store_resend_igmp(struct device *d,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	int new_value, ret = count;
	struct bonding *bond = to_bond(d);

	if (sscanf(buf, "%d", &new_value) != 1) {
		pr_err("%s: no resend_igmp value specified.\n",
		       bond->dev->name);
		ret = -EINVAL;
		goto out;
	}

	if (new_value < 0 || new_value > 255) {
		pr_err("%s: Invalid resend_igmp value %d not in range 0-255; rejected.\n",
		       bond->dev->name, new_value);
		ret = -EINVAL;
		goto out;
	}

	pr_info("%s: Setting resend_igmp to %d.\n",
		bond->dev->name, new_value);
	bond->params.resend_igmp = new_value;
out:
	return ret;
}