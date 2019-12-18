#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; scalar_t__ link_type; int unique_id; int /*<<< orphan*/  initial_mtu; int /*<<< orphan*/  guestlan; } ;
struct TYPE_11__ {scalar_t__* hsuid; } ;
struct qeth_card {TYPE_4__* dev; int /*<<< orphan*/  napi; TYPE_3__* gdev; TYPE_2__ info; TYPE_1__ options; } ;
struct TYPE_14__ {int dev_id; int features; int gso_max_size; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  mtu; int /*<<< orphan*/  watchdog_timeo; struct qeth_card* ml_priv; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 int NETIF_F_GRO ; 
 int NETIF_F_HW_VLAN_FILTER ; 
 int NETIF_F_HW_VLAN_RX ; 
 int NETIF_F_HW_VLAN_TX ; 
 int PAGE_SIZE ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CARD_TYPE_OSD ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 scalar_t__ QETH_LINK_TYPE_HSTR ; 
 scalar_t__ QETH_LINK_TYPE_LANE_TR ; 
 int /*<<< orphan*/  QETH_NAPI_WEIGHT ; 
 int /*<<< orphan*/  QETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int UNIQUE_ID_NOT_BY_CARD ; 
 TYPE_4__* alloc_etherdev (int /*<<< orphan*/ ) ; 
 TYPE_4__* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* alloc_trdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  netif_napi_add (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_ethtool_ops ; 
 int /*<<< orphan*/  qeth_l3_get_unique_id (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_iqd_read_initial_mac (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_netdev_ops ; 
 int /*<<< orphan*/  qeth_l3_osa_netdev_ops ; 
 int /*<<< orphan*/  qeth_l3_poll ; 
 int register_netdev (TYPE_4__*) ; 

__attribute__((used)) static int qeth_l3_setup_netdev(struct qeth_card *card)
{
	if (card->info.type == QETH_CARD_TYPE_OSD ||
	    card->info.type == QETH_CARD_TYPE_OSX) {
		if ((card->info.link_type == QETH_LINK_TYPE_LANE_TR) ||
		    (card->info.link_type == QETH_LINK_TYPE_HSTR)) {
#ifdef CONFIG_TR
			card->dev = alloc_trdev(0);
#endif
			if (!card->dev)
				return -ENODEV;
			card->dev->netdev_ops = &qeth_l3_netdev_ops;
		} else {
			card->dev = alloc_etherdev(0);
			if (!card->dev)
				return -ENODEV;
			card->dev->netdev_ops = &qeth_l3_osa_netdev_ops;

			/*IPv6 address autoconfiguration stuff*/
			qeth_l3_get_unique_id(card);
			if (!(card->info.unique_id & UNIQUE_ID_NOT_BY_CARD))
				card->dev->dev_id = card->info.unique_id &
							 0xffff;
			if (!card->info.guestlan)
				card->dev->features |= NETIF_F_GRO;
		}
	} else if (card->info.type == QETH_CARD_TYPE_IQD) {
		card->dev = alloc_netdev(0, "hsi%d", ether_setup);
		if (!card->dev)
			return -ENODEV;
		card->dev->flags |= IFF_NOARP;
		card->dev->netdev_ops = &qeth_l3_netdev_ops;
		qeth_l3_iqd_read_initial_mac(card);
		if (card->options.hsuid[0])
			memcpy(card->dev->perm_addr, card->options.hsuid, 9);
	} else
		return -ENODEV;

	card->dev->ml_priv = card;
	card->dev->watchdog_timeo = QETH_TX_TIMEOUT;
	card->dev->mtu = card->info.initial_mtu;
	SET_ETHTOOL_OPS(card->dev, &qeth_l3_ethtool_ops);
	card->dev->features |=	NETIF_F_HW_VLAN_TX |
				NETIF_F_HW_VLAN_RX |
				NETIF_F_HW_VLAN_FILTER;
	card->dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
	card->dev->gso_max_size = 15 * PAGE_SIZE;

	SET_NETDEV_DEV(card->dev, &card->gdev->dev);
	netif_napi_add(card->dev, &card->napi, qeth_l3_poll, QETH_NAPI_WEIGHT);
	return register_netdev(card->dev);
}