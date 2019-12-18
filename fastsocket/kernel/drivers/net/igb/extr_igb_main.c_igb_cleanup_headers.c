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
typedef  union e1000_adv_rx_desc {int dummy; } e1000_adv_rx_desc ;
struct sk_buff {int len; } ;
struct igb_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  igb_pull_tail (struct igb_ring*,union e1000_adv_rx_desc*,struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 scalar_t__ skb_pad (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool igb_cleanup_headers(struct igb_ring *rx_ring,
				union e1000_adv_rx_desc *rx_desc,
				struct sk_buff *skb)
{

	/* place header in linear portion of buffer */
	if (skb_is_nonlinear(skb))
		igb_pull_tail(rx_ring, rx_desc, skb);

	/* if skb_pad returns an error the skb was freed */
	if (unlikely(skb->len < 60)) {
		int pad_len = 60 - skb->len;

		if (skb_pad(skb, pad_len))
			return true;
		__skb_put(skb, pad_len);
	}

	return false;
}