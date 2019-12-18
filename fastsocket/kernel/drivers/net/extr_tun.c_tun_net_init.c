#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tun_struct {int flags; } ;
struct net_device {int mtu; int flags; void* tx_queue_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NONE ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 void* TUN_READQ_SIZE ; 
#define  TUN_TAP_DEV 129 
#define  TUN_TUN_DEV 128 
 int TUN_TYPE_MASK ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_netdev_ops ; 
 int /*<<< orphan*/  tun_netdev_ops ; 

__attribute__((used)) static void tun_net_init(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	switch (tun->flags & TUN_TYPE_MASK) {
	case TUN_TUN_DEV:
		dev->netdev_ops = &tun_netdev_ops;

		/* Point-to-Point TUN Device */
		dev->hard_header_len = 0;
		dev->addr_len = 0;
		dev->mtu = 1500;

		/* Zero header length */
		dev->type = ARPHRD_NONE;
		dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
		dev->tx_queue_len = TUN_READQ_SIZE;  /* We prefer our own queue length */
		break;

	case TUN_TAP_DEV:
		dev->netdev_ops = &tap_netdev_ops;
		/* Ethernet TAP Device */
		ether_setup(dev);
		netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;

		random_ether_addr(dev->dev_addr);

		dev->tx_queue_len = TUN_READQ_SIZE;  /* We prefer our own queue length */
		break;
	}
}