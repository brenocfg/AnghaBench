#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usbnet {int maxpacket; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int INT51X1_HEADER_SIZE ; 
 scalar_t__ __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *int51x1_tx_fixup(struct usbnet *dev,
		struct sk_buff *skb, gfp_t flags)
{
	int pack_len = skb->len;
	int pack_with_header_len = pack_len + INT51X1_HEADER_SIZE;
	int headroom = skb_headroom(skb);
	int tailroom = skb_tailroom(skb);
	int need_tail = 0;
	__le16 *len;

	/* if packet and our header is smaler than 64 pad to 64 (+ ZLP) */
	if ((pack_with_header_len) < dev->maxpacket)
		need_tail = dev->maxpacket - pack_with_header_len + 1;
	/*
	 * usbnet would send a ZLP if packetlength mod urbsize == 0 for us,
	 * but we need to know ourself, because this would add to the length
	 * we send down to the device...
	 */
	else if (!(pack_with_header_len % dev->maxpacket))
		need_tail = 1;

	if (!skb_cloned(skb) &&
			(headroom + tailroom >= need_tail + INT51X1_HEADER_SIZE)) {
		if (headroom < INT51X1_HEADER_SIZE || tailroom < need_tail) {
			skb->data = memmove(skb->head + INT51X1_HEADER_SIZE,
					skb->data, skb->len);
			skb_set_tail_pointer(skb, skb->len);
		}
	} else {
		struct sk_buff *skb2;

		skb2 = skb_copy_expand(skb,
				INT51X1_HEADER_SIZE,
				need_tail,
				flags);
		dev_kfree_skb_any(skb);
		if (!skb2)
			return NULL;
		skb = skb2;
	}

	pack_len += need_tail;
	pack_len &= 0x07ff;

	len = (__le16 *) __skb_push(skb, INT51X1_HEADER_SIZE);
	*len = cpu_to_le16(pack_len);

	if(need_tail)
		memset(__skb_put(skb, need_tail), 0, need_tail);

	return skb;
}