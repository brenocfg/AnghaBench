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
struct sk_buff {TYPE_2__* dev; int /*<<< orphan*/  protocol; } ;
struct mcs_cb {TYPE_2__* netdev; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IRDA ; 
 int /*<<< orphan*/  IRDA_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mcs_unwrap_fir(struct mcs_cb *mcs, __u8 *buf, int len)
{
	__u32 fcs;
	int new_len;
	struct sk_buff *skb;

	/* Assume that the frames are going to fill a single packet
	 * rather than span multiple packets.  This is most likely a false
	 * assumption.
	 */

	new_len = len - 4;
	if(unlikely(new_len <= 0)) {
		IRDA_ERROR("%s short frame length %d\n",
			   mcs->netdev->name, new_len);
		++mcs->netdev->stats.rx_errors;
		++mcs->netdev->stats.rx_length_errors;
		return;
	}

	fcs = ~(crc32_le(~0, buf, new_len));
	if(fcs != get_unaligned_le32(buf + new_len)) {
		IRDA_ERROR("crc error calc 0x%x len %d\n", fcs, new_len);
		mcs->netdev->stats.rx_errors++;
		mcs->netdev->stats.rx_crc_errors++;
		return;
	}

	skb = dev_alloc_skb(new_len + 1);
	if(unlikely(!skb)) {
		++mcs->netdev->stats.rx_dropped;
		return;
	}

	skb_reserve(skb, 1);
	skb_copy_to_linear_data(skb, buf, new_len);
	skb_put(skb, new_len);
	skb_reset_mac_header(skb);
	skb->protocol = htons(ETH_P_IRDA);
	skb->dev = mcs->netdev;

	netif_rx(skb);

	mcs->netdev->stats.rx_packets++;
	mcs->netdev->stats.rx_bytes += new_len;

	return;
}