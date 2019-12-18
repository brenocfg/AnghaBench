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
struct net_device {char* name; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void bond_destroy_slave_symlinks(struct net_device *master,
				 struct net_device *slave)
{
	char linkname[IFNAMSIZ+7];

	sysfs_remove_link(&(slave->dev.kobj), "master");
	sprintf(linkname, "slave_%s", slave->name);
	sysfs_remove_link(&(master->dev.kobj), linkname);
}