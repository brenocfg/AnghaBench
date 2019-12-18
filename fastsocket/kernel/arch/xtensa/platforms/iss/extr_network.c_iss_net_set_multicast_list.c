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
struct net_device {int flags; scalar_t__ mc_count; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 

__attribute__((used)) static void iss_net_set_multicast_list(struct net_device *dev)
{
#if 0
	if (dev->flags & IFF_PROMISC)
		return;
	else if (dev->mc_count)
		dev->flags |= IFF_ALLMULTI;
	else
		dev->flags &= ~IFF_ALLMULTI;
#endif
}