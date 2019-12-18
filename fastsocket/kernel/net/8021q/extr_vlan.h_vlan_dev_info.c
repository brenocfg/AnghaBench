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
struct vlan_dev_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vlan_dev_info* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static inline struct vlan_dev_info *vlan_dev_info(const struct net_device *dev)
{
	return netdev_priv(dev);
}