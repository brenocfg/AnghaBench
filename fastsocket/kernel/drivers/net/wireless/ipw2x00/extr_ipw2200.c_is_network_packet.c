#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct libipw_hdr_4addr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr3; } ;
struct ipw_priv {TYPE_2__* net_dev; int /*<<< orphan*/  bssid; TYPE_1__* ieee; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
#define  IW_MODE_ADHOC 129 
#define  IW_MODE_INFRA 128 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_network_packet(struct ipw_priv *priv,
				    struct libipw_hdr_4addr *header)
{
	/* Filter incoming packets to determine if they are targeted toward
	 * this network, discarding packets coming from ourselves */
	switch (priv->ieee->iw_mode) {
	case IW_MODE_ADHOC:	/* Header: Dest. | Source    | BSSID */
		/* packets from our adapter are dropped (echo) */
		if (!memcmp(header->addr2, priv->net_dev->dev_addr, ETH_ALEN))
			return 0;

		/* {broad,multi}cast packets to our BSSID go through */
		if (is_multicast_ether_addr(header->addr1))
			return !memcmp(header->addr3, priv->bssid, ETH_ALEN);

		/* packets to our adapter go through */
		return !memcmp(header->addr1, priv->net_dev->dev_addr,
			       ETH_ALEN);

	case IW_MODE_INFRA:	/* Header: Dest. | BSSID | Source */
		/* packets from our adapter are dropped (echo) */
		if (!memcmp(header->addr3, priv->net_dev->dev_addr, ETH_ALEN))
			return 0;

		/* {broad,multi}cast packets to our BSS go through */
		if (is_multicast_ether_addr(header->addr1))
			return !memcmp(header->addr2, priv->bssid, ETH_ALEN);

		/* packets to our adapter go through */
		return !memcmp(header->addr1, priv->net_dev->dev_addr,
			       ETH_ALEN);
	}

	return 1;
}