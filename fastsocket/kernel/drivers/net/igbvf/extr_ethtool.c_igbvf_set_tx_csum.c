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
struct net_device {int features; } ;

/* Variables and functions */
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 

__attribute__((used)) static int igbvf_set_tx_csum(struct net_device *netdev, u32 data)
{
	if (data)
		netdev->features |= (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM);
	else
		netdev->features &= ~(NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM);
	return 0;
}