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

/* Variables and functions */
 unsigned long NETIF_F_ALL_CSUM ; 
 unsigned long NETIF_F_ALL_FOR_ALL ; 
 unsigned long NETIF_F_GEN_CSUM ; 
 unsigned long NETIF_F_NO_CSUM ; 
 unsigned long NETIF_F_ONE_FOR_ALL ; 
 unsigned long NETIF_F_VLAN_CHALLENGED ; 

unsigned long netdev_increment_features(unsigned long all, unsigned long one,
					unsigned long mask)
{
	if (mask & NETIF_F_GEN_CSUM)
		mask |= NETIF_F_ALL_CSUM;
	mask |= NETIF_F_VLAN_CHALLENGED;

	all |= one & (NETIF_F_ONE_FOR_ALL|NETIF_F_ALL_CSUM) & mask;
	all &= one | ~NETIF_F_ALL_FOR_ALL;

	/* If device needs checksumming, downgrade to it. */
	if (all & (NETIF_F_ALL_CSUM & ~NETIF_F_NO_CSUM))
		all &= ~NETIF_F_NO_CSUM;

	/* If one device supports hw checksumming, set for all. */
	if (all & NETIF_F_GEN_CSUM)
		all &= ~(NETIF_F_ALL_CSUM & ~NETIF_F_GEN_CSUM);

	return all;
}