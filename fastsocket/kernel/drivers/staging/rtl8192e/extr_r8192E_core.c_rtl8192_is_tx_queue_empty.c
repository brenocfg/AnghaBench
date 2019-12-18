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
struct r8192_priv {TYPE_1__* tx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int HCCA_QUEUE ; 
 int MGNT_QUEUE ; 
 int TXCMD_QUEUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int,scalar_t__) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

short rtl8192_is_tx_queue_empty(struct net_device *dev)
{
	int i=0;
	struct r8192_priv *priv = ieee80211_priv(dev);
	for (i=0; i<=MGNT_QUEUE; i++)
	{
		if ((i== TXCMD_QUEUE) || (i == HCCA_QUEUE) )
			continue;
		if (skb_queue_len(&(&priv->tx_ring[i])->queue) > 0){
			printk("===>tx queue is not empty:%d, %d\n", i, skb_queue_len(&(&priv->tx_ring[i])->queue));
			return 0;
		}
	}
	return 1;
}