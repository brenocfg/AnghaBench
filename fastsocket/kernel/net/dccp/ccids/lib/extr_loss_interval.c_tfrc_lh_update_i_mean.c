#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct tfrc_loss_interval {int li_is_closed; scalar_t__ li_length; int /*<<< orphan*/  li_ccval; int /*<<< orphan*/  li_seqno; } ;
struct tfrc_loss_hist {scalar_t__ i_mean; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dccph_ccval; } ;

/* Variables and functions */
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int SUB16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_delta_seqno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tfrc_lh_calc_i_mean (struct tfrc_loss_hist*) ; 
 int tfrc_lh_length (struct tfrc_loss_hist*) ; 
 struct tfrc_loss_interval* tfrc_lh_peek (struct tfrc_loss_hist*) ; 

u8 tfrc_lh_update_i_mean(struct tfrc_loss_hist *lh, struct sk_buff *skb)
{
	struct tfrc_loss_interval *cur = tfrc_lh_peek(lh);
	u32 old_i_mean = lh->i_mean;
	s64 len;

	if (cur == NULL)			/* not initialised */
		return 0;

	len = dccp_delta_seqno(cur->li_seqno, DCCP_SKB_CB(skb)->dccpd_seq) + 1;

	if (len - (s64)cur->li_length <= 0)	/* duplicate or reordered */
		return 0;

	if (SUB16(dccp_hdr(skb)->dccph_ccval, cur->li_ccval) > 4)
		/*
		 * Implements RFC 4342, 10.2:
		 * If a packet S (skb) exists whose seqno comes `after' the one
		 * starting the current loss interval (cur) and if the modulo-16
		 * distance from C(cur) to C(S) is greater than 4, consider all
		 * subsequent packets as belonging to a new loss interval. This
		 * test is necessary since CCVal may wrap between intervals.
		 */
		cur->li_is_closed = 1;

	if (tfrc_lh_length(lh) == 1)		/* due to RFC 3448, 6.3.1 */
		return 0;

	cur->li_length = len;
	tfrc_lh_calc_i_mean(lh);

	return (lh->i_mean < old_i_mean);
}