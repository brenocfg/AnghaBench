#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int /*<<< orphan*/  name; scalar_t__ mc_count; } ;
struct TYPE_5__ {TYPE_4__* ctrl_urb; int /*<<< orphan*/  flags; int /*<<< orphan*/ * eth_regs; } ;
typedef  TYPE_1__ pegasus_t ;
struct TYPE_6__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_REGS_CHANGE ; 
 size_t EthCtrl0 ; 
 size_t EthCtrl2 ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RX_MULTICAST ; 
 int /*<<< orphan*/  RX_PROMISCUOUS ; 
 int /*<<< orphan*/  ctrl_callback (TYPE_4__*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pegasus_set_multicast(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);

	if (net->flags & IFF_PROMISC) {
		pegasus->eth_regs[EthCtrl2] |= RX_PROMISCUOUS;
		if (netif_msg_link(pegasus))
			pr_info("%s: Promiscuous mode enabled.\n", net->name);
	} else if (net->mc_count || (net->flags & IFF_ALLMULTI)) {
		pegasus->eth_regs[EthCtrl0] |= RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
		if (netif_msg_link(pegasus))
			pr_debug("%s: set allmulti\n", net->name);
	} else {
		pegasus->eth_regs[EthCtrl0] &= ~RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
	}

	pegasus->ctrl_urb->status = 0;

	pegasus->flags |= ETH_REGS_CHANGE;
	ctrl_callback(pegasus->ctrl_urb);
}