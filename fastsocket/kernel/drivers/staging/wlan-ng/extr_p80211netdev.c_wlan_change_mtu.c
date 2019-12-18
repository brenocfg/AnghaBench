#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mtu; } ;
typedef  TYPE_1__ netdevice_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int wlan_change_mtu(netdevice_t *dev, int new_mtu)
{
	/* 2312 is max 802.11 payload, 20 is overhead, (ether + llc +snap)
	   and another 8 for wep. */
	if ((new_mtu < 68) || (new_mtu > (2312 - 20 - 8)))
		return -EINVAL;

	dev->mtu = new_mtu;

	return 0;
}