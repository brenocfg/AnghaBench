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
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_ECN ; 

__attribute__((used)) static int bnx2x_set_tso(struct net_device *dev, u32 data)
{
	if (data) {
		dev->features |= (NETIF_F_TSO | NETIF_F_TSO_ECN);
		dev->features |= NETIF_F_TSO6;
	} else {
		dev->features &= ~(NETIF_F_TSO | NETIF_F_TSO_ECN);
		dev->features &= ~NETIF_F_TSO6;
	}

	return 0;
}