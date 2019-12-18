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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {TYPE_1__ dev; } ;
struct bonding {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bonding_group ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bond_create_sysfs_entry(struct bonding *bond)
{
	struct net_device *dev = bond->dev;
	int err;

	err = sysfs_create_group(&(dev->dev.kobj), &bonding_group);
	if (err)
		pr_emerg("eek! didn't create group!\n");

	return err;
}