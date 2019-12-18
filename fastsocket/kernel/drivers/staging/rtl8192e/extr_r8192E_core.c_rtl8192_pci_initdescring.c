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
typedef  short u32 ;
struct r8192_priv {int txringcount; TYPE_1__* tx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ desc; } ;

/* Variables and functions */
 int MAX_TX_QUEUE_COUNT ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 short rtl8192_alloc_rx_desc_ring (struct net_device*) ; 
 short rtl8192_alloc_tx_desc_ring (struct net_device*,int,int) ; 
 int /*<<< orphan*/  rtl8192_free_rx_ring (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_free_tx_ring (struct net_device*,int) ; 

__attribute__((used)) static short rtl8192_pci_initdescring(struct net_device *dev)
{
    u32 ret;
    int i;
    struct r8192_priv *priv = ieee80211_priv(dev);

    ret = rtl8192_alloc_rx_desc_ring(dev);
    if (ret) {
        return ret;
    }


    /* general process for other queue */
    for (i = 0; i < MAX_TX_QUEUE_COUNT; i++) {
        if ((ret = rtl8192_alloc_tx_desc_ring(dev, i, priv->txringcount)))
            goto err_free_rings;
    }

#if 0
    /* specific process for hardware beacon process */
    if ((ret = rtl8192_alloc_tx_desc_ring(dev, MAX_TX_QUEUE_COUNT - 1, 2)))
        goto err_free_rings;
#endif

    return 0;

err_free_rings:
    rtl8192_free_rx_ring(dev);
    for (i = 0; i < MAX_TX_QUEUE_COUNT; i++)
        if (priv->tx_ring[i].desc)
            rtl8192_free_tx_ring(dev, i);
    return 1;
}