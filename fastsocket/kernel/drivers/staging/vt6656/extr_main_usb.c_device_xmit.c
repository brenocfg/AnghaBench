#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ bLinkPass; scalar_t__ bStopDataPkt; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct net_device_stats stats; } ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TYPE_AC0DMA ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ nsDMA_tx_packet (TYPE_1__*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int  device_xmit(struct sk_buff *skb, struct net_device *dev) {
    PSDevice    pDevice=netdev_priv(dev);
    struct net_device_stats* pStats = &pDevice->stats;


    spin_lock_irq(&pDevice->lock);

    netif_stop_queue(pDevice->dev);

    if (pDevice->bLinkPass == FALSE) {
        dev_kfree_skb_irq(skb);
        spin_unlock_irq(&pDevice->lock);
        return 0;
    }
    if (pDevice->bStopDataPkt == TRUE) {
        dev_kfree_skb_irq(skb);
        pStats->tx_dropped++;
        spin_unlock_irq(&pDevice->lock);
        return 0;
    }

    if(nsDMA_tx_packet(pDevice, TYPE_AC0DMA, skb) !=0) {  //mike add:xmit fail!
         if (netif_queue_stopped(pDevice->dev))
              netif_wake_queue(pDevice->dev);
    }

    spin_unlock_irq(&pDevice->lock);

    return 0;
}