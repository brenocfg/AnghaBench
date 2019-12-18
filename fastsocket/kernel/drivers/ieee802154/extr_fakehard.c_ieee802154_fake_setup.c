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
struct net_device {int needed_tailroom; int mtu; int tx_queue_len; int flags; int /*<<< orphan*/  destructor; scalar_t__ watchdog_timeo; int /*<<< orphan*/  type; int /*<<< orphan*/  features; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE802154 ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  NETIF_F_NO_CSUM ; 
 int /*<<< orphan*/  ieee802154_fake_destruct ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee802154_fake_setup(struct net_device *dev)
{
	dev->addr_len		= IEEE802154_ADDR_LEN;
	memset(dev->broadcast, 0xff, IEEE802154_ADDR_LEN);
	dev->features		= NETIF_F_NO_CSUM;
	dev->needed_tailroom	= 2; /* FCS */
	dev->mtu		= 127;
	dev->tx_queue_len	= 10;
	dev->type		= ARPHRD_IEEE802154;
	dev->flags		= IFF_NOARP | IFF_BROADCAST;
	dev->watchdog_timeo	= 0;
	dev->destructor		= ieee802154_fake_destruct;
}