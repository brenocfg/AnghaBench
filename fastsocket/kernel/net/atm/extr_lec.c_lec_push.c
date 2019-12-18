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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int len; int* data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  truesize; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int flags; int addr_len; TYPE_1__ stats; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct lecdatahdr_8025 {unsigned char* h_dest; unsigned char* h_source; } ;
struct lecdatahdr_8023 {unsigned char* h_dest; unsigned char* h_source; } ;
struct lec_priv {scalar_t__ is_trdev; int /*<<< orphan*/  lec_arp_empty_ones; int /*<<< orphan*/  is_proxy; int /*<<< orphan*/  lec_arp_lock; int /*<<< orphan*/  lecd; int /*<<< orphan*/  lecid; } ;
struct lec_arp_table {struct atm_vcc* vcc; } ;
struct atm_vcc {int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; scalar_t__ proto_data; } ;
struct atm_skb_data {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_SKB (struct sk_buff*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lec_arp_check_empties (struct lec_priv*,struct atm_vcc*,struct sk_buff*) ; 
 struct lec_arp_table* lec_arp_find (struct lec_priv*,unsigned char*) ; 
 int /*<<< orphan*/  lec_arp_put (struct lec_arp_table*) ; 
 int /*<<< orphan*/  lec_arp_remove (struct lec_priv*,struct lec_arp_table*) ; 
 int /*<<< orphan*/  lec_ctrl_magic ; 
 scalar_t__ lec_is_data_direct (struct atm_vcc*) ; 
 int /*<<< orphan*/  lec_vcc_close (struct lec_priv*,struct atm_vcc*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  printk (char*,char*,...) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int) ; 
 int /*<<< orphan*/  tr_type_trans (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void lec_push(struct atm_vcc *vcc, struct sk_buff *skb)
{
	unsigned long flags;
	struct net_device *dev = (struct net_device *)vcc->proto_data;
	struct lec_priv *priv = netdev_priv(dev);

#if DUMP_PACKETS >0
	int i = 0;
	char buf[300];

	printk("%s: lec_push vcc vpi:%d vci:%d\n", dev->name,
	       vcc->vpi, vcc->vci);
#endif
	if (!skb) {
		pr_debug("%s: null skb\n", dev->name);
		lec_vcc_close(priv, vcc);
		return;
	}
#if DUMP_PACKETS > 0
	printk("%s: rcv datalen:%ld lecid:%4.4x\n", dev->name,
	       skb->len, priv->lecid);
#if DUMP_PACKETS >= 2
	for (i = 0; i < skb->len && i < 99; i++) {
		sprintf(buf + i * 3, "%2.2x ", 0xff & skb->data[i]);
	}
#elif DUMP_PACKETS >= 1
	for (i = 0; i < skb->len && i < 30; i++) {
		sprintf(buf + i * 3, "%2.2x ", 0xff & skb->data[i]);
	}
#endif /* DUMP_PACKETS >= 1 */
	if (i == skb->len)
		printk("%s\n", buf);
	else
		printk("%s...\n", buf);
#endif /* DUMP_PACKETS > 0 */
	if (memcmp(skb->data, lec_ctrl_magic, 4) == 0) {	/* Control frame, to daemon */
		struct sock *sk = sk_atm(vcc);

		pr_debug("%s: To daemon\n", dev->name);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_ready(sk, skb->len);
	} else {		/* Data frame, queue to protocol handlers */
		struct lec_arp_table *entry;
		unsigned char *src, *dst;

		atm_return(vcc, skb->truesize);
		if (*(__be16 *) skb->data == htons(priv->lecid) ||
		    !priv->lecd || !(dev->flags & IFF_UP)) {
			/*
			 * Probably looping back, or if lecd is missing,
			 * lecd has gone down
			 */
			pr_debug("Ignoring frame...\n");
			dev_kfree_skb(skb);
			return;
		}
#ifdef CONFIG_TR
		if (priv->is_trdev)
			dst = ((struct lecdatahdr_8025 *)skb->data)->h_dest;
		else
#endif
			dst = ((struct lecdatahdr_8023 *)skb->data)->h_dest;

		/*
		 * If this is a Data Direct VCC, and the VCC does not match
		 * the LE_ARP cache entry, delete the LE_ARP cache entry.
		 */
		spin_lock_irqsave(&priv->lec_arp_lock, flags);
		if (lec_is_data_direct(vcc)) {
#ifdef CONFIG_TR
			if (priv->is_trdev)
				src =
				    ((struct lecdatahdr_8025 *)skb->data)->
				    h_source;
			else
#endif
				src =
				    ((struct lecdatahdr_8023 *)skb->data)->
				    h_source;
			entry = lec_arp_find(priv, src);
			if (entry && entry->vcc != vcc) {
				lec_arp_remove(priv, entry);
				lec_arp_put(entry);
			}
		}
		spin_unlock_irqrestore(&priv->lec_arp_lock, flags);

		if (!(dst[0] & 0x01) &&	/* Never filter Multi/Broadcast */
		    !priv->is_proxy &&	/* Proxy wants all the packets */
		    memcmp(dst, dev->dev_addr, dev->addr_len)) {
			dev_kfree_skb(skb);
			return;
		}
		if (!hlist_empty(&priv->lec_arp_empty_ones)) {
			lec_arp_check_empties(priv, vcc, skb);
		}
		skb_pull(skb, 2);	/* skip lec_id */
#ifdef CONFIG_TR
		if (priv->is_trdev)
			skb->protocol = tr_type_trans(skb, dev);
		else
#endif
			skb->protocol = eth_type_trans(skb, dev);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		memset(ATM_SKB(skb), 0, sizeof(struct atm_skb_data));
		netif_rx(skb);
	}
}