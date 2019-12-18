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
struct r8180_priv {int* txmapring; int txringcount; int* txbkpring; int* txbepring; int* txvipring; int* txvopring; int* txhpring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

short rtl8180_is_tx_queue_empty(struct net_device *dev){

	struct r8180_priv *priv = ieee80211_priv(dev);
	u32* d;

	for (d = priv->txmapring;
		d < priv->txmapring + priv->txringcount;d+=8)
			if(*d & (1<<31)) return 0;

	for (d = priv->txbkpring;
		d < priv->txbkpring + priv->txringcount;d+=8)
			if(*d & (1<<31)) return 0;

	for (d = priv->txbepring;
		d < priv->txbepring + priv->txringcount;d+=8)
			if(*d & (1<<31)) return 0;

	for (d = priv->txvipring;
		d < priv->txvipring + priv->txringcount;d+=8)
			if(*d & (1<<31)) return 0;

	for (d = priv->txvopring;
		d < priv->txvopring + priv->txringcount;d+=8)
			if(*d & (1<<31)) return 0;

	for (d = priv->txhpring;
		d < priv->txhpring + priv->txringcount;d+=8)
			if(*d & (1<<31)) return 0;
	return 1;
}