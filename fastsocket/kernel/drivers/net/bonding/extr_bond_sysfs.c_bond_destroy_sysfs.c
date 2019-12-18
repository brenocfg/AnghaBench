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

/* Variables and functions */
 int /*<<< orphan*/  class_attr_bonding_masters ; 
 int /*<<< orphan*/  netdev_class_remove_file (int /*<<< orphan*/ *) ; 

void bond_destroy_sysfs(void)
{
	netdev_class_remove_file(&class_attr_bonding_masters);
}