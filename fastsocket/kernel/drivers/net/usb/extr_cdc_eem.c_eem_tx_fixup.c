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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct usbnet {int maxpacket; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BIT (int) ; 
 int EEM_HEAD ; 
 int ETH_FCS_LEN ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *eem_tx_fixup(struct usbnet *dev, struct sk_buff *skb,
				       gfp_t flags)
{
	struct sk_buff	*skb2 = NULL;
	u16		len = skb->len;
	u32		crc = 0;
	int		padlen = 0;

	/* When ((len + EEM_HEAD + ETH_FCS_LEN) % dev->maxpacket) is
	 * zero, stick two bytes of zero length EEM packet on the end.
	 * Else the framework would add invalid single byte padding,
	 * since it can't know whether ZLPs will be handled right by
	 * all the relevant hardware and software.
	 */
	if (!((len + EEM_HEAD + ETH_FCS_LEN) % dev->maxpacket))
		padlen += 2;

	if (!skb_cloned(skb)) {
		int	headroom = skb_headroom(skb);
		int	tailroom = skb_tailroom(skb);

		if ((tailroom >= ETH_FCS_LEN + padlen)
				&& (headroom >= EEM_HEAD))
			goto done;

		if ((headroom + tailroom)
				> (EEM_HEAD + ETH_FCS_LEN + padlen)) {
			skb->data = memmove(skb->head +
					EEM_HEAD,
					skb->data,
					skb->len);
			skb_set_tail_pointer(skb, len);
			goto done;
		}
	}

	skb2 = skb_copy_expand(skb, EEM_HEAD, ETH_FCS_LEN + padlen, flags);
	if (!skb2)
		return NULL;

	dev_kfree_skb_any(skb);
	skb = skb2;

done:
	/* we don't use the "no Ethernet CRC" option */
	crc = crc32_le(~0, skb->data, skb->len);
	crc = ~crc;

	put_unaligned_le32(crc, skb_put(skb, 4));

	/* EEM packet header format:
	 * b0..13:	length of ethernet frame
	 * b14:		bmCRC (1 == valid Ethernet CRC)
	 * b15:		bmType (0 == data)
	 */
	len = skb->len;
	put_unaligned_le16(BIT(14) | len, skb_push(skb, 2));

	/* Bundle a zero length EEM packet if needed */
	if (padlen)
		put_unaligned_le16(0, skb_put(skb, 2));

	return skb;
}