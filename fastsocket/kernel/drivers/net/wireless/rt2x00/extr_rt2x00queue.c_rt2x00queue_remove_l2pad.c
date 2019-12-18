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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int L2PAD_SIZE (unsigned int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 

void rt2x00queue_remove_l2pad(struct sk_buff *skb, unsigned int header_length)
{
	/*
	 * L2 padding is only present if the skb contains more than just the
	 * IEEE 802.11 header.
	 */
	unsigned int l2pad = (skb->len > header_length) ?
				L2PAD_SIZE(header_length) : 0;

	if (!l2pad)
		return;

	memmove(skb->data + l2pad, skb->data, header_length);
	skb_pull(skb, l2pad);
}