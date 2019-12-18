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
struct TYPE_3__ {int /*<<< orphan*/  TxBuffAddr; scalar_t__ OWN; } ;
typedef  TYPE_1__ tx_desc_819x_pci ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl8192_tx_ring {size_t idx; int entries; int /*<<< orphan*/  queue; TYPE_1__* desc; } ;
struct r8192_priv {int /*<<< orphan*/  irq_tx_tasklet; TYPE_2__* ieee80211; int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ ack_tx_to_ieee; } ;

/* Variables and functions */
 int BEACON_QUEUE ; 
 int MGNT_QUEUE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_ps_tx_ack (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl8192_is_tx_queue_empty (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8192_tx_isr(struct net_device *dev, int prio)
{
    struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);

    struct rtl8192_tx_ring *ring = &priv->tx_ring[prio];

    while (skb_queue_len(&ring->queue)) {
        tx_desc_819x_pci *entry = &ring->desc[ring->idx];
        struct sk_buff *skb;

        /* beacon packet will only use the first descriptor defautly,
         * and the OWN may not be cleared by the hardware
         * */
        if(prio != BEACON_QUEUE) {
            if(entry->OWN)
                return;
            ring->idx = (ring->idx + 1) % ring->entries;
        }

        skb = __skb_dequeue(&ring->queue);
        pci_unmap_single(priv->pdev, le32_to_cpu(entry->TxBuffAddr),
                skb->len, PCI_DMA_TODEVICE);

        kfree_skb(skb);
    }
    if (prio == MGNT_QUEUE){
        if (priv->ieee80211->ack_tx_to_ieee){
            if (rtl8192_is_tx_queue_empty(dev)){
                priv->ieee80211->ack_tx_to_ieee = 0;
                ieee80211_ps_tx_ack(priv->ieee80211, 1);
            }
        }
    }

    if(prio != BEACON_QUEUE) {
        /* try to deal with the pending packets  */
        tasklet_schedule(&priv->irq_tx_tasklet);
    }

}