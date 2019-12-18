#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; int broadcast_capable; int /*<<< orphan*/  initial_mtu; } ;
struct qeth_card {TYPE_3__* dev; int /*<<< orphan*/  napi; TYPE_2__* gdev; TYPE_1__ info; } ;
struct TYPE_10__ {int /*<<< orphan*/  features; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  mtu; int /*<<< orphan*/  watchdog_timeo; struct qeth_card* ml_priv; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_FILTER ; 
#define  QETH_CARD_TYPE_IQD 129 
#define  QETH_CARD_TYPE_OSN 128 
 int /*<<< orphan*/  QETH_NAPI_WEIGHT ; 
 int /*<<< orphan*/  QETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* alloc_etherdev (int /*<<< orphan*/ ) ; 
 void* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  netif_napi_add (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_ethtool_ops ; 
 int /*<<< orphan*/  qeth_l2_netdev_ops ; 
 int /*<<< orphan*/  qeth_l2_osn_ops ; 
 int /*<<< orphan*/  qeth_l2_poll ; 
 int /*<<< orphan*/  qeth_l2_request_initial_mac (struct qeth_card*) ; 
 int register_netdev (TYPE_3__*) ; 

__attribute__((used)) static int qeth_l2_setup_netdev(struct qeth_card *card)
{
	switch (card->info.type) {
	case QETH_CARD_TYPE_IQD:
		card->dev = alloc_netdev(0, "hsi%d", ether_setup);
		break;
	case QETH_CARD_TYPE_OSN:
		card->dev = alloc_netdev(0, "osn%d", ether_setup);
		card->dev->flags |= IFF_NOARP;
		break;
	default:
		card->dev = alloc_etherdev(0);
	}

	if (!card->dev)
		return -ENODEV;

	card->dev->ml_priv = card;
	card->dev->watchdog_timeo = QETH_TX_TIMEOUT;
	card->dev->mtu = card->info.initial_mtu;
	card->dev->netdev_ops = &qeth_l2_netdev_ops;
	if (card->info.type != QETH_CARD_TYPE_OSN)
		SET_ETHTOOL_OPS(card->dev, &qeth_l2_ethtool_ops);
	else
		SET_ETHTOOL_OPS(card->dev, &qeth_l2_osn_ops);
	card->dev->features |= NETIF_F_HW_VLAN_FILTER;
	card->info.broadcast_capable = 1;
	qeth_l2_request_initial_mac(card);
	SET_NETDEV_DEV(card->dev, &card->gdev->dev);
	netif_napi_add(card->dev, &card->napi, qeth_l2_poll, QETH_NAPI_WEIGHT);
	return register_netdev(card->dev);
}