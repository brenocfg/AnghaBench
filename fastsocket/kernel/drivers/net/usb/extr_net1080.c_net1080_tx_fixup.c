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
typedef  int u16 ;
struct usbnet {int /*<<< orphan*/  xid; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
struct nc_trailer {int /*<<< orphan*/  packet_id; } ;
struct nc_header {void* packet_id; void* packet_len; void* hdr_len; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_BYTE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,void*,void*,void*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
net1080_tx_fixup(struct usbnet *dev, struct sk_buff *skb, gfp_t flags)
{
	struct sk_buff		*skb2;
	struct nc_header	*header = NULL;
	struct nc_trailer	*trailer = NULL;
	int			padlen = sizeof (struct nc_trailer);
	int			len = skb->len;

	if (!((len + padlen + sizeof (struct nc_header)) & 0x01))
		padlen++;
	if (!skb_cloned(skb)) {
		int	headroom = skb_headroom(skb);
		int	tailroom = skb_tailroom(skb);

		if (padlen <= tailroom &&
		    sizeof(struct nc_header) <= headroom)
			/* There's enough head and tail room */
			goto encapsulate;

		if ((sizeof (struct nc_header) + padlen) <
				(headroom + tailroom)) {
			/* There's enough total room, so just readjust */
			skb->data = memmove(skb->head
						+ sizeof (struct nc_header),
					    skb->data, skb->len);
			skb_set_tail_pointer(skb, len);
			goto encapsulate;
		}
	}

	/* Create a new skb to use with the correct size */
	skb2 = skb_copy_expand(skb,
				sizeof (struct nc_header),
				padlen,
				flags);
	dev_kfree_skb_any(skb);
	if (!skb2)
		return skb2;
	skb = skb2;

encapsulate:
	/* header first */
	header = (struct nc_header *) skb_push(skb, sizeof *header);
	header->hdr_len = cpu_to_le16(sizeof (*header));
	header->packet_len = cpu_to_le16(len);
	header->packet_id = cpu_to_le16((u16)dev->xid++);

	/* maybe pad; then trailer */
	if (!((skb->len + sizeof *trailer) & 0x01))
		*skb_put(skb, 1) = PAD_BYTE;
	trailer = (struct nc_trailer *) skb_put(skb, sizeof *trailer);
	put_unaligned(header->packet_id, &trailer->packet_id);
#if 0
	devdbg(dev, "frame >tx h %d p %d id %d",
		header->hdr_len, header->packet_len,
		header->packet_id);
#endif
	return skb;
}