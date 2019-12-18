#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uipdev_s ;
struct uip_netif {int mtu; int hwaddr_len; scalar_t__ hwaddr; int /*<<< orphan*/  flags; int /*<<< orphan*/  linkoutput; int /*<<< orphan*/  output; int /*<<< orphan*/ * name; } ;
struct uip_eth_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; struct uip_eth_addr* ethaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAME0 ; 
 int /*<<< orphan*/  IFNAME1 ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_NETIF_FLAG_BROADCAST ; 
 int /*<<< orphan*/  __bba_link_tx ; 
 int /*<<< orphan*/  __bba_start_tx ; 
 TYPE_1__ bba_device ; 
 struct uip_netif* bba_netif ; 

uipdev_s uip_bba_create(struct uip_netif *dev)
{
	dev->name[0] = IFNAME0;
	dev->name[1] = IFNAME1;

	dev->output = __bba_start_tx;
	dev->linkoutput = __bba_link_tx;
	dev->mtu = 1500;
	dev->flags = UIP_NETIF_FLAG_BROADCAST;
	dev->hwaddr_len = 6;

	bba_device.ethaddr = (struct uip_eth_addr*)dev->hwaddr;
	bba_device.state = UIP_ERR_OK;

	bba_netif = dev;
	return &bba_device;
}