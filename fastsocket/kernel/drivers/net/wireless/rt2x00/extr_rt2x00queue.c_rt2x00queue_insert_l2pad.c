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
struct sk_buff {unsigned int len; scalar_t__ data; } ;

/* Variables and functions */
 unsigned int ALIGN_SIZE (struct sk_buff*,unsigned int) ; 
 unsigned int L2PAD_SIZE (unsigned int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,unsigned int) ; 

void rt2x00queue_insert_l2pad(struct sk_buff *skb, unsigned int header_length)
{
	unsigned int payload_length = skb->len - header_length;
	unsigned int header_align = ALIGN_SIZE(skb, 0);
	unsigned int payload_align = ALIGN_SIZE(skb, header_length);
	unsigned int l2pad = payload_length ? L2PAD_SIZE(header_length) : 0;

	/*
	 * Adjust the header alignment if the payload needs to be moved more
	 * than the header.
	 */
	if (payload_align > header_align)
		header_align += 4;

	/* There is nothing to do if no alignment is needed */
	if (!header_align)
		return;

	/* Reserve the amount of space needed in front of the frame */
	skb_push(skb, header_align);

	/*
	 * Move the header.
	 */
	memmove(skb->data, skb->data + header_align, header_length);

	/* Move the payload, if present and if required */
	if (payload_length && payload_align)
		memmove(skb->data + header_length + l2pad,
			skb->data + header_length + l2pad + payload_align,
			payload_length);

	/* Trim the skb to the correct size */
	skb_trim(skb, header_length + l2pad + payload_length);
}