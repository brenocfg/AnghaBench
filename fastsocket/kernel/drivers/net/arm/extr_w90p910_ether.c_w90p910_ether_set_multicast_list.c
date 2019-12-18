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
struct w90p910_ether {scalar_t__ reg; } ;
struct net_device {int flags; scalar_t__ mc_list; } ;

/* Variables and functions */
 unsigned int CAMCMR_ABP ; 
 unsigned int CAMCMR_AMP ; 
 unsigned int CAMCMR_AUP ; 
 unsigned int CAMCMR_ECMP ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ REG_CAMCMR ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void w90p910_ether_set_multicast_list(struct net_device *dev)
{
	struct w90p910_ether *ether;
	unsigned int rx_mode;

	ether = netdev_priv(dev);

	if (dev->flags & IFF_PROMISC)
		rx_mode = CAMCMR_AUP | CAMCMR_AMP | CAMCMR_ABP | CAMCMR_ECMP;
	else if ((dev->flags & IFF_ALLMULTI) || dev->mc_list)
			rx_mode = CAMCMR_AMP | CAMCMR_ABP | CAMCMR_ECMP;
		else
				rx_mode = CAMCMR_ECMP | CAMCMR_ABP;
	__raw_writel(rx_mode, ether->reg + REG_CAMCMR);
}