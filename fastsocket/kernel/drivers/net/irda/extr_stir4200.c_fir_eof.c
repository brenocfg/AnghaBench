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
struct TYPE_6__ {int len; int truesize; scalar_t__ head; scalar_t__ data; struct sk_buff* skb; } ;
struct stir_cb {TYPE_2__* netdev; TYPE_3__ rx_buff; } ;
struct sk_buff {TYPE_2__* dev; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
typedef  TYPE_3__ iobuff_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IRDA ; 
 int IRDA_RX_COPY_THRESHOLD ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void fir_eof(struct stir_cb *stir)
{
	iobuff_t *rx_buff = &stir->rx_buff;
	int len = rx_buff->len - 4;
	struct sk_buff *skb, *nskb;
	__u32 fcs;

	if (unlikely(len <= 0)) {
		pr_debug("%s: short frame len %d\n",
			 stir->netdev->name, len);

		++stir->netdev->stats.rx_errors;
		++stir->netdev->stats.rx_length_errors;
		return;
	}

	fcs = ~(crc32_le(~0, rx_buff->data, len));
	if (fcs != get_unaligned_le32(rx_buff->data + len)) {
		pr_debug("crc error calc 0x%x len %d\n", fcs, len);
		stir->netdev->stats.rx_errors++;
		stir->netdev->stats.rx_crc_errors++;
		return;
	}

	/* if frame is short then just copy it */
	if (len < IRDA_RX_COPY_THRESHOLD) {
		nskb = dev_alloc_skb(len + 1);
		if (unlikely(!nskb)) {
			++stir->netdev->stats.rx_dropped;
			return;
		}
		skb_reserve(nskb, 1);
		skb = nskb;
		skb_copy_to_linear_data(nskb, rx_buff->data, len);
	} else {
		nskb = dev_alloc_skb(rx_buff->truesize);
		if (unlikely(!nskb)) {
			++stir->netdev->stats.rx_dropped;
			return;
		}
		skb_reserve(nskb, 1);
		skb = rx_buff->skb;
		rx_buff->skb = nskb;
		rx_buff->head = nskb->data;
	}

	skb_put(skb, len);

	skb_reset_mac_header(skb);
	skb->protocol = htons(ETH_P_IRDA);
	skb->dev = stir->netdev;

	netif_rx(skb);

	stir->netdev->stats.rx_packets++;
	stir->netdev->stats.rx_bytes += len;

	rx_buff->data = rx_buff->head;
	rx_buff->len = 0;
}