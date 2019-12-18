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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (struct device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_sas_phy_delete ; 

void sas_remove_children(struct device *dev)
{
	device_for_each_child(dev, (void *)0, do_sas_phy_delete);
	device_for_each_child(dev, (void *)1, do_sas_phy_delete);
}