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
typedef  int /*<<< orphan*/  u32 ;
struct vlan_dev_info {int /*<<< orphan*/  real_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_ethtool_get_rx_csum (int /*<<< orphan*/ ) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static u32 vlan_ethtool_get_rx_csum(struct net_device *dev)
{
	const struct vlan_dev_info *vlan = vlan_dev_info(dev);
	return dev_ethtool_get_rx_csum(vlan->real_dev);
}