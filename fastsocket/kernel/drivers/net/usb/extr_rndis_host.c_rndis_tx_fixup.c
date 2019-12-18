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
struct usbnet {int dummy; } ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
struct rndis_data_hdr {void* data_len; void* data_offset; void* msg_len; int /*<<< orphan*/  msg_type; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_MSG_PACKET ; 
 scalar_t__ __skb_push (struct sk_buff*,int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct rndis_data_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *
rndis_tx_fixup(struct usbnet *dev, struct sk_buff *skb, gfp_t flags)
{
	struct rndis_data_hdr	*hdr;
	struct sk_buff		*skb2;
	unsigned		len = skb->len;

	if (likely(!skb_cloned(skb))) {
		int	room = skb_headroom(skb);

		/* enough head room as-is? */
		if (unlikely((sizeof *hdr) <= room))
			goto fill;

		/* enough room, but needs to be readjusted? */
		room += skb_tailroom(skb);
		if (likely((sizeof *hdr) <= room)) {
			skb->data = memmove(skb->head + sizeof *hdr,
					    skb->data, len);
			skb_set_tail_pointer(skb, len);
			goto fill;
		}
	}

	/* create a new skb, with the correct size (and tailpad) */
	skb2 = skb_copy_expand(skb, sizeof *hdr, 1, flags);
	dev_kfree_skb_any(skb);
	if (unlikely(!skb2))
		return skb2;
	skb = skb2;

	/* fill out the RNDIS header.  we won't bother trying to batch
	 * packets; Linux minimizes wasted bandwidth through tx queues.
	 */
fill:
	hdr = (void *) __skb_push(skb, sizeof *hdr);
	memset(hdr, 0, sizeof *hdr);
	hdr->msg_type = RNDIS_MSG_PACKET;
	hdr->msg_len = cpu_to_le32(skb->len);
	hdr->data_offset = cpu_to_le32(sizeof(*hdr) - 8);
	hdr->data_len = cpu_to_le32(len);

	/* FIXME make the last packet always be short ... */
	return skb;
}