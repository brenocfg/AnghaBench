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
struct net_device {int dummy; } ;
struct ethtool_ops_ext {int dummy; } ;
struct TYPE_2__ {struct ethtool_ops_ext const* ethtool_ops_ext; } ;

/* Variables and functions */
 TYPE_1__* netdev_extended (struct net_device*) ; 

void set_ethtool_ops_ext(struct net_device *netdev, const struct ethtool_ops_ext *ops)
{
	netdev_extended(netdev)->ethtool_ops_ext = ops;
}