#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct sk_buff {int dummy; } ;
struct rtl8169_private {TYPE_3__* dev; scalar_t__ TxDescArray; TYPE_1__* pci_dev; struct ring_info* tx_skb; } ;
struct ring_info {unsigned int len; struct sk_buff* skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int NUM_TX_DESC ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl8169_unmap_tx_skb (int /*<<< orphan*/ *,struct ring_info*,scalar_t__) ; 

__attribute__((used)) static void rtl8169_tx_clear_range(struct rtl8169_private *tp, u32 start,
				   unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++) {
		unsigned int entry = (start + i) % NUM_TX_DESC;
		struct ring_info *tx_skb = tp->tx_skb + entry;
		unsigned int len = tx_skb->len;

		if (len) {
			struct sk_buff *skb = tx_skb->skb;

			rtl8169_unmap_tx_skb(&tp->pci_dev->dev, tx_skb,
					     tp->TxDescArray + entry);
			if (skb) {
				tp->dev->stats.tx_dropped++;
				dev_kfree_skb(skb);
				tx_skb->skb = NULL;
			}
		}
	}
}