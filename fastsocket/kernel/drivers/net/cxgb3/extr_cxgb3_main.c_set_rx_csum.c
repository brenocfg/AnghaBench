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
struct port_info {int rx_offload; int first_qset; int nqsets; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int T3_LRO ; 
 int T3_RX_CSUM ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_qset_lro (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_rx_csum(struct net_device *dev, u32 data)
{
	struct port_info *p = netdev_priv(dev);

	if (data) {
		p->rx_offload |= T3_RX_CSUM;
	} else {
		int i;

		p->rx_offload &= ~(T3_RX_CSUM | T3_LRO);
		for (i = p->first_qset; i < p->first_qset + p->nqsets; i++)
			set_qset_lro(dev, i, 0);
	}
	return 0;
}