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
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* real_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* vlan_dev_info (struct net_device const*) ; 

void vlan_dev_get_realdev_name(const struct net_device *dev, char *result)
{
	strncpy(result, vlan_dev_info(dev)->real_dev->name, 23);
}