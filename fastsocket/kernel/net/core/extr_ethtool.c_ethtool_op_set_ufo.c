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
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_UFO ; 

int ethtool_op_set_ufo(struct net_device *dev, u32 data)
{
	if (data)
		dev->features |= NETIF_F_UFO;
	else
		dev->features &= ~NETIF_F_UFO;
	return 0;
}