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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct txdesc {int dummy; } ;
struct skb_frag_struct {int /*<<< orphan*/  size; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  page; } ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct jme_ring {struct jme_buffer_info* bufinf; struct txdesc* desc; } ;
struct jme_buffer_info {int dummy; } ;
struct jme_adapter {int tx_ring_mask; int /*<<< orphan*/  pdev; TYPE_1__* dev; struct jme_ring* txring; } ;
struct TYPE_4__ {int nr_frags; struct skb_frag_struct* frags; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  jme_fill_tx_map (int /*<<< orphan*/ ,struct txdesc*,struct jme_buffer_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jme_map_tx_skb(struct jme_adapter *jme, struct sk_buff *skb, int idx)
{
	struct jme_ring *txring = &(jme->txring[0]);
	struct txdesc *txdesc = txring->desc, *ctxdesc;
	struct jme_buffer_info *txbi = txring->bufinf, *ctxbi;
	u8 hidma = jme->dev->features & NETIF_F_HIGHDMA;
	int i, nr_frags = skb_shinfo(skb)->nr_frags;
	int mask = jme->tx_ring_mask;
	struct skb_frag_struct *frag;
	u32 len;

	for (i = 0 ; i < nr_frags ; ++i) {
		frag = &skb_shinfo(skb)->frags[i];
		ctxdesc = txdesc + ((idx + i + 2) & (mask));
		ctxbi = txbi + ((idx + i + 2) & (mask));

		jme_fill_tx_map(jme->pdev, ctxdesc, ctxbi, frag->page,
				 frag->page_offset, frag->size, hidma);
	}

	len = skb_is_nonlinear(skb) ? skb_headlen(skb) : skb->len;
	ctxdesc = txdesc + ((idx + 1) & (mask));
	ctxbi = txbi + ((idx + 1) & (mask));
	jme_fill_tx_map(jme->pdev, ctxdesc, ctxbi, virt_to_page(skb->data),
			offset_in_page(skb->data), len, hidma);

}