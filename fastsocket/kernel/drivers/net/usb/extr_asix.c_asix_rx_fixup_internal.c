#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct usbnet {TYPE_1__* net; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct asix_rx_fixup_info {int size; int split_head; int header; int /*<<< orphan*/ * ax_skb; } ;
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * netdev_alloc_skb_ip_align (TYPE_1__*,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*,int,...) ; 
 unsigned char* skb_put (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbnet_skb_return (struct usbnet*,int /*<<< orphan*/ *) ; 

int asix_rx_fixup_internal(struct usbnet *dev, struct sk_buff *skb,
			   struct asix_rx_fixup_info *rx)
{
	int offset = 0;

	while (offset + sizeof(u16) <= skb->len) {
		u16 remaining = 0;
		unsigned char *data;

		if (!rx->size) {
			if ((skb->len - offset == sizeof(u16)) ||
			    rx->split_head) {
				if(!rx->split_head) {
					rx->header = get_unaligned_le16(
							skb->data + offset);
					rx->split_head = true;
					offset += sizeof(u16);
					break;
				} else {
					rx->header |= (get_unaligned_le16(
							skb->data + offset)
							<< 16);
					rx->split_head = false;
					offset += sizeof(u16);
				}
			} else {
				rx->header = get_unaligned_le32(skb->data +
								offset);
				offset += sizeof(u32);
			}

			/* get the packet length */
			rx->size = (u16) (rx->header & 0x7ff);
			if (rx->size != ((~rx->header >> 16) & 0x7ff)) {
				netdev_err(dev->net, "asix_rx_fixup() Bad Header Length 0x%x, offset %d\n",
					   rx->header, offset);
				rx->size = 0;
				return 0;
			}
			rx->ax_skb = netdev_alloc_skb_ip_align(dev->net,
							       rx->size);
			if (!rx->ax_skb)
				return 0;
		}

		if (rx->size > dev->net->mtu + ETH_HLEN + VLAN_HLEN) {
			netdev_err(dev->net, "asix_rx_fixup() Bad RX Length %d\n",
				   rx->size);
			kfree_skb(rx->ax_skb);
			rx->ax_skb = NULL;
			rx->size = 0U;

			return 0;
		}

		if (rx->size > skb->len - offset) {
			remaining = rx->size - (skb->len - offset);
			rx->size = skb->len - offset;
		}

		data = skb_put(rx->ax_skb, rx->size);
		memcpy(data, skb->data + offset, rx->size);
		if (!remaining)
			usbnet_skb_return(dev, rx->ax_skb);

		offset += (rx->size + 1) & 0xfffe;
		rx->size = remaining;
	}

	if (skb->len != offset) {
		netdev_err(dev->net, "asix_rx_fixup() Bad SKB Length %d, %d\n",
			   skb->len, offset);
		return 0;
	}

	return 1;
}