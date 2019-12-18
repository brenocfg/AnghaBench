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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct gelic_card {int ether_port_status; struct net_device** netdev; } ;

/* Variables and functions */
 int GELIC_LV1_ETHER_LINK_UP ; 
 int /*<<< orphan*/  GELIC_LV1_GET_ETH_PORT_STATUS ; 
 int /*<<< orphan*/  GELIC_LV1_VLAN_TX_ETHERNET ; 
 size_t GELIC_PORT_ETHERNET ; 
 int /*<<< orphan*/  bus_id (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_id (struct gelic_card*) ; 
 int /*<<< orphan*/  lv1_net_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static void gelic_card_get_ether_port_status(struct gelic_card *card,
					     int inform)
{
	u64 v2;
	struct net_device *ether_netdev;

	lv1_net_control(bus_id(card), dev_id(card),
			GELIC_LV1_GET_ETH_PORT_STATUS,
			GELIC_LV1_VLAN_TX_ETHERNET, 0, 0,
			&card->ether_port_status, &v2);

	if (inform) {
		ether_netdev = card->netdev[GELIC_PORT_ETHERNET];
		if (card->ether_port_status & GELIC_LV1_ETHER_LINK_UP)
			netif_carrier_on(ether_netdev);
		else
			netif_carrier_off(ether_netdev);
	}
}