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
struct TYPE_3__ {int flags; int /*<<< orphan*/  vlan; int /*<<< orphan*/  mss; int /*<<< orphan*/  pktsize; } ;
struct txdesc {TYPE_1__ desc1; scalar_t__* dw; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct jme_ring {struct jme_buffer_info* bufinf; scalar_t__ desc; } ;
struct jme_buffer_info {unsigned long start_xmit; int /*<<< orphan*/  len; struct sk_buff* skb; scalar_t__ nr_desc; } ;
struct jme_adapter {struct jme_ring* txring; } ;
struct TYPE_4__ {scalar_t__ nr_frags; } ;

/* Variables and functions */
 int TXFLAG_INT ; 
 int TXFLAG_OWN ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jme_map_tx_skb (struct jme_adapter*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  jme_tx_csum (struct jme_adapter*,struct sk_buff*,int*) ; 
 scalar_t__ jme_tx_tso (struct sk_buff*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  jme_tx_vlan (struct sk_buff*,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
jme_fill_tx_desc(struct jme_adapter *jme, struct sk_buff *skb, int idx)
{
	struct jme_ring *txring = &(jme->txring[0]);
	struct txdesc *txdesc;
	struct jme_buffer_info *txbi;
	u8 flags;

	txdesc = (struct txdesc *)txring->desc + idx;
	txbi = txring->bufinf + idx;

	txdesc->dw[0] = 0;
	txdesc->dw[1] = 0;
	txdesc->dw[2] = 0;
	txdesc->dw[3] = 0;
	txdesc->desc1.pktsize = cpu_to_le16(skb->len);
	/*
	 * Set OWN bit at final.
	 * When kernel transmit faster than NIC.
	 * And NIC trying to send this descriptor before we tell
	 * it to start sending this TX queue.
	 * Other fields are already filled correctly.
	 */
	wmb();
	flags = TXFLAG_OWN | TXFLAG_INT;
	/*
	 * Set checksum flags while not tso
	 */
	if (jme_tx_tso(skb, &txdesc->desc1.mss, &flags))
		jme_tx_csum(jme, skb, &flags);
	jme_tx_vlan(skb, &txdesc->desc1.vlan, &flags);
	jme_map_tx_skb(jme, skb, idx);
	txdesc->desc1.flags = flags;
	/*
	 * Set tx buffer info after telling NIC to send
	 * For better tx_clean timing
	 */
	wmb();
	txbi->nr_desc = skb_shinfo(skb)->nr_frags + 2;
	txbi->skb = skb;
	txbi->len = skb->len;
	txbi->start_xmit = jiffies;
	if (!txbi->start_xmit)
		txbi->start_xmit = (0UL-1);

	return 0;
}