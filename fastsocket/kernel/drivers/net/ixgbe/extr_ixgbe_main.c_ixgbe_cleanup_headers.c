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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct sk_buff {int len; } ;
struct ixgbe_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_FRAME_ERR_MASK ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_pull_tail (struct ixgbe_ring*,struct sk_buff*) ; 
 scalar_t__ ixgbe_rx_is_fcoe (struct ixgbe_ring*,union ixgbe_adv_rx_desc*) ; 
 int ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 scalar_t__ skb_pad (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ixgbe_cleanup_headers(struct ixgbe_ring *rx_ring,
				  union ixgbe_adv_rx_desc *rx_desc,
				  struct sk_buff *skb)
{
	/* verify that the packet does not have any known errors */
	if (unlikely(ixgbe_test_staterr(rx_desc,
					IXGBE_RXDADV_ERR_FRAME_ERR_MASK))) {
		dev_kfree_skb_any(skb);
		return true;
	}

	/* place header in linear portion of buffer */
	if (skb_is_nonlinear(skb))
		ixgbe_pull_tail(rx_ring, skb);

#ifdef IXGBE_FCOE
	/* do not attempt to pad FCoE Frames as this will disrupt DDP */
	if (ixgbe_rx_is_fcoe(rx_ring, rx_desc))
		return false;

#endif
	/* if skb_pad returns an error the skb was freed */
	if (unlikely(skb->len < 60)) {
		int pad_len = 60 - skb->len;

		if (skb_pad(skb, pad_len))
			return true;
		__skb_put(skb, pad_len);
	}

	return false;
}