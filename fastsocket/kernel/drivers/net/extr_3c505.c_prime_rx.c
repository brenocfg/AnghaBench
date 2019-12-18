#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ rx_active; int /*<<< orphan*/  itx_pcb; } ;
typedef  TYPE_1__ elp_device ;

/* Variables and functions */
 scalar_t__ ELP_RX_PCBS ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  start_receive (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void prime_rx(struct net_device *dev)
{
	elp_device *adapter = netdev_priv(dev);
	while (adapter->rx_active < ELP_RX_PCBS && netif_running(dev)) {
		if (!start_receive(dev, &adapter->itx_pcb))
			break;
	}
}