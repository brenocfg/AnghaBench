#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int len; int data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_5__ {void* h_proto; struct TYPE_5__* h_source; struct TYPE_5__* h_dest; } ;
struct bnep_session {TYPE_2__ eh; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  BNEP_COMPRESSED 131 
#define  BNEP_COMPRESSED_DST_ONLY 130 
#define  BNEP_COMPRESSED_SRC_ONLY 129 
 size_t BNEP_CONTROL ; 
 size_t BNEP_EXT_HEADER ; 
#define  BNEP_GENERAL 128 
 size_t BNEP_RX_TYPES ; 
 size_t BNEP_TYPE_MASK ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* __bnep_rx_hlen ; 
 scalar_t__ __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnep_rx_control (struct bnep_session*,int,int) ; 
 scalar_t__ bnep_rx_extension (struct bnep_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 void* get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int ntohs (void*) ; 
 int /*<<< orphan*/  put_unaligned (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__,int) ; 
 TYPE_2__* skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static inline int bnep_rx_frame(struct bnep_session *s, struct sk_buff *skb)
{
	struct net_device *dev = s->dev;
	struct sk_buff *nskb;
	u8 type;

	dev->stats.rx_bytes += skb->len;

	type = *(u8 *) skb->data; skb_pull(skb, 1);

	if ((type & BNEP_TYPE_MASK) > BNEP_RX_TYPES)
		goto badframe;

	if ((type & BNEP_TYPE_MASK) == BNEP_CONTROL) {
		bnep_rx_control(s, skb->data, skb->len);
		kfree_skb(skb);
		return 0;
	}

	skb_reset_mac_header(skb);

	/* Verify and pull out header */
	if (!skb_pull(skb, __bnep_rx_hlen[type & BNEP_TYPE_MASK]))
		goto badframe;

	s->eh.h_proto = get_unaligned((__be16 *) (skb->data - 2));

	if (type & BNEP_EXT_HEADER) {
		if (bnep_rx_extension(s, skb) < 0)
			goto badframe;
	}

	/* Strip 802.1p header */
	if (ntohs(s->eh.h_proto) == 0x8100) {
		if (!skb_pull(skb, 4))
			goto badframe;
		s->eh.h_proto = get_unaligned((__be16 *) (skb->data - 2));
	}

	/* We have to alloc new skb and copy data here :(. Because original skb
	 * may not be modified and because of the alignment requirements. */
	nskb = alloc_skb(2 + ETH_HLEN + skb->len, GFP_KERNEL);
	if (!nskb) {
		dev->stats.rx_dropped++;
		kfree_skb(skb);
		return -ENOMEM;
	}
	skb_reserve(nskb, 2);

	/* Decompress header and construct ether frame */
	switch (type & BNEP_TYPE_MASK) {
	case BNEP_COMPRESSED:
		memcpy(__skb_put(nskb, ETH_HLEN), &s->eh, ETH_HLEN);
		break;

	case BNEP_COMPRESSED_SRC_ONLY:
		memcpy(__skb_put(nskb, ETH_ALEN), s->eh.h_dest, ETH_ALEN);
		memcpy(__skb_put(nskb, ETH_ALEN), skb_mac_header(skb), ETH_ALEN);
		put_unaligned(s->eh.h_proto, (__be16 *) __skb_put(nskb, 2));
		break;

	case BNEP_COMPRESSED_DST_ONLY:
		memcpy(__skb_put(nskb, ETH_ALEN), skb_mac_header(skb),
		       ETH_ALEN);
		memcpy(__skb_put(nskb, ETH_ALEN + 2), s->eh.h_source,
		       ETH_ALEN + 2);
		break;

	case BNEP_GENERAL:
		memcpy(__skb_put(nskb, ETH_ALEN * 2), skb_mac_header(skb),
		       ETH_ALEN * 2);
		put_unaligned(s->eh.h_proto, (__be16 *) __skb_put(nskb, 2));
		break;
	}

	skb_copy_from_linear_data(skb, __skb_put(nskb, skb->len), skb->len);
	kfree_skb(skb);

	dev->stats.rx_packets++;
	nskb->ip_summed = CHECKSUM_NONE;
	nskb->protocol  = eth_type_trans(nskb, dev);
	netif_rx_ni(nskb);
	return 0;

badframe:
	dev->stats.rx_errors++;
	kfree_skb(skb);
	return 0;
}