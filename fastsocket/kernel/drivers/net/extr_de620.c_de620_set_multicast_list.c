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
 int RXALL ; 
 int RXPBM ; 
 int TCR_DEF ; 
 int /*<<< orphan*/  W_TCR ; 
 int /*<<< orphan*/  de620_set_register (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void de620_set_multicast_list(struct net_device *dev)
{
	if (dev->mc_count || dev->flags&(IFF_ALLMULTI|IFF_PROMISC))
	{ /* Enable promiscuous mode */
		de620_set_register(dev, W_TCR, (TCR_DEF & ~RXPBM) | RXALL);
	}
	else
	{ /* Disable promiscuous mode, use normal mode */
		de620_set_register(dev, W_TCR, TCR_DEF);
	}
}