#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ attr; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ __dev_get_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ class_attr_bonding_masters ; 
 int /*<<< orphan*/  init_net ; 
 int netdev_class_create_file (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int bond_create_sysfs(void)
{
	int ret;

	ret = netdev_class_create_file(&class_attr_bonding_masters);
	/*
	 * Permit multiple loads of the module by ignoring failures to
	 * create the bonding_masters sysfs file.  Bonding devices
	 * created by second or subsequent loads of the module will
	 * not be listed in, or controllable by, bonding_masters, but
	 * will have the usual "bonding" sysfs directory.
	 *
	 * This is done to preserve backwards compatibility for
	 * initscripts/sysconfig, which load bonding multiple times to
	 * configure multiple bonding devices.
	 */
	if (ret == -EEXIST) {
		/* Is someone being kinky and naming a device bonding_master? */
		if (__dev_get_by_name(&init_net,
				      class_attr_bonding_masters.attr.name))
			pr_err("network device named %s already "
			       "exists in sysfs",
			       class_attr_bonding_masters.attr.name);
		ret = 0;
	}

	return ret;

}