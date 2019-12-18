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
typedef  int u32 ;
struct r8180_priv {int* txmapring; int txringcount; int* txbkpring; int* txbepring; int* txvipring; int* txvopring; int* txhpring; int* txbeaconring; int txbeaconcount; int* txmapringtail; int* txmapringhead; int* txbkpringtail; int* txbkpringhead; int* txbepringtail; int* txbepringhead; int* txvipringtail; int* txvipringhead; int* txvopringtail; int* txvopringhead; int* txhpringtail; int* txhpringhead; int* txbeaconringtail; scalar_t__ ack_tx_to_ieee; int /*<<< orphan*/  ieee80211; int /*<<< orphan*/  txbeaconbufs; int /*<<< orphan*/  txbeaconbufstail; int /*<<< orphan*/  txhpbufs; int /*<<< orphan*/  txhpbufstail; int /*<<< orphan*/  txvopbufs; int /*<<< orphan*/  txvopbufstail; int /*<<< orphan*/  txvipbufs; int /*<<< orphan*/  txvipbufstail; int /*<<< orphan*/  txbepbufs; int /*<<< orphan*/  txbepbufstail; int /*<<< orphan*/  txbkpbufs; int /*<<< orphan*/  txbkpbufstail; int /*<<< orphan*/  txmapbufs; int /*<<< orphan*/  txmapbufstail; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nic_txring (struct net_device*) ; 

void fix_tx_fifo(struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	u32 *tmp;
	int i;

	for (tmp=priv->txmapring, i=0;
	     i < priv->txringcount;
	     tmp+=8, i++){
		*tmp = *tmp &~ (1<<31);
	}

	for (tmp=priv->txbkpring, i=0;
	     i < priv->txringcount;
	     tmp+=8, i++) {
		*tmp = *tmp &~ (1<<31);
	}

	for (tmp=priv->txbepring, i=0;
	     i < priv->txringcount;
	     tmp+=8, i++){
		*tmp = *tmp &~ (1<<31);
	}
	for (tmp=priv->txvipring, i=0;
	     i < priv->txringcount;
	     tmp+=8, i++) {
		*tmp = *tmp &~ (1<<31);
	}

	for (tmp=priv->txvopring, i=0;
	     i < priv->txringcount;
	     tmp+=8, i++){
		*tmp = *tmp &~ (1<<31);
	}

	for (tmp=priv->txhpring, i=0;
	     i < priv->txringcount;
	     tmp+=8,i++){
		*tmp = *tmp &~ (1<<31);
	}

	for (tmp=priv->txbeaconring, i=0;
	     i < priv->txbeaconcount;
	     tmp+=8, i++){
		*tmp = *tmp &~ (1<<31);
	}

	priv->txmapringtail = priv->txmapring;
	priv->txmapringhead = priv->txmapring;
	priv->txmapbufstail = priv->txmapbufs;

	priv->txbkpringtail = priv->txbkpring;
	priv->txbkpringhead = priv->txbkpring;
	priv->txbkpbufstail = priv->txbkpbufs;

	priv->txbepringtail = priv->txbepring;
	priv->txbepringhead = priv->txbepring;
	priv->txbepbufstail = priv->txbepbufs;

	priv->txvipringtail = priv->txvipring;
	priv->txvipringhead = priv->txvipring;
	priv->txvipbufstail = priv->txvipbufs;

	priv->txvopringtail = priv->txvopring;
	priv->txvopringhead = priv->txvopring;
	priv->txvopbufstail = priv->txvopbufs;

	priv->txhpringtail = priv->txhpring;
	priv->txhpringhead = priv->txhpring;
	priv->txhpbufstail = priv->txhpbufs;

	priv->txbeaconringtail = priv->txbeaconring;
	priv->txbeaconbufstail = priv->txbeaconbufs;
	set_nic_txring(dev);

	ieee80211_reset_queue(priv->ieee80211);
	priv->ack_tx_to_ieee = 0;
}