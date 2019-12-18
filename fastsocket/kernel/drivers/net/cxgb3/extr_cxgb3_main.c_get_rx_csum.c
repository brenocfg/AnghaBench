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
typedef  int u32 ;
struct port_info {int rx_offload; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int T3_RX_CSUM ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 get_rx_csum(struct net_device *dev)
{
	struct port_info *p = netdev_priv(dev);

	return p->rx_offload & T3_RX_CSUM;
}