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
typedef  size_t u32 ;
struct r8192_priv {int /*<<< orphan*/  ieee80211; TYPE_1__* tx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 size_t MAX_TX_QUEUE_COUNT ; 
 int /*<<< orphan*/ * TX_DESC_BASE ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8192_tx_enable(struct net_device *dev)
{
    struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
    u32 i;
    for (i = 0; i < MAX_TX_QUEUE_COUNT; i++)
        write_nic_dword(dev, TX_DESC_BASE[i], priv->tx_ring[i].dma);

    ieee80211_reset_queue(priv->ieee80211);
}