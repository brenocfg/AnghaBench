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
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPIDER_NET_MAX_MTU ; 
 int SPIDER_NET_MIN_MTU ; 

__attribute__((used)) static int
spider_net_change_mtu(struct net_device *netdev, int new_mtu)
{
	/* no need to re-alloc skbs or so -- the max mtu is about 2.3k
	 * and mtu is outbound only anyway */
	if ( (new_mtu < SPIDER_NET_MIN_MTU ) ||
		(new_mtu > SPIDER_NET_MAX_MTU) )
		return -EINVAL;
	netdev->mtu = new_mtu;
	return 0;
}