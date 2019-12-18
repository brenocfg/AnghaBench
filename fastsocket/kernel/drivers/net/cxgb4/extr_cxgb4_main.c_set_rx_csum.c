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
struct port_info {int /*<<< orphan*/  rx_offload; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CSO ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int set_rx_csum(struct net_device *dev, u32 data)
{
	struct port_info *p = netdev_priv(dev);

	if (data)
		p->rx_offload |= RX_CSO;
	else
		p->rx_offload &= ~RX_CSO;
	return 0;
}