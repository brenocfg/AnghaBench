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
struct skb_frame_desc {int flags; int /*<<< orphan*/ * iv; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int SKBDESC_IV_STRIPPED ; 
 struct skb_frame_desc* get_skb_frame_desc (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int const) ; 

void rt2x00crypto_tx_insert_iv(struct sk_buff *skb, unsigned int header_length)
{
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(skb);
	const unsigned int iv_len =
	    ((!!(skbdesc->iv[0])) * 4) + ((!!(skbdesc->iv[1])) * 4);

	if (!(skbdesc->flags & SKBDESC_IV_STRIPPED))
		return;

	skb_push(skb, iv_len);

	/* Move ieee80211 header */
	memmove(skb->data, skb->data + iv_len, header_length);

	/* Copy IV/EIV data */
	memcpy(skb->data + header_length, skbdesc->iv, iv_len);

	/* IV/EIV data has returned into the frame */
	skbdesc->flags &= ~SKBDESC_IV_STRIPPED;
}