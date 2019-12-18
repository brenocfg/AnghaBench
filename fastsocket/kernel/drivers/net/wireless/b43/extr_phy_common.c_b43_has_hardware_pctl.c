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
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  hardware_power_control; } ;
struct b43_wldev {TYPE_2__ phy; } ;
struct TYPE_3__ {int (* supports_hwpctl ) (struct b43_wldev*) ;} ;

/* Variables and functions */
 int stub1 (struct b43_wldev*) ; 

bool b43_has_hardware_pctl(struct b43_wldev *dev)
{
	if (!dev->phy.hardware_power_control)
		return 0;
	if (!dev->phy.ops->supports_hwpctl)
		return 0;
	return dev->phy.ops->supports_hwpctl(dev);
}