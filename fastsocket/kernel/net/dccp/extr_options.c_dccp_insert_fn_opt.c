#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ dccpd_opt_len; } ;

/* Variables and functions */
 scalar_t__ DCCP_MAX_OPT_LEN ; 
 int DCCP_SINGLE_OPT_MAXLEN ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_WARN (char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

int dccp_insert_fn_opt(struct sk_buff *skb, u8 type, u8 feat,
		       u8 *val, u8 len, bool repeat_first)
{
	u8 tot_len, *to;

	/* take the `Feature' field and possible repetition into account */
	if (len > (DCCP_SINGLE_OPT_MAXLEN - 2)) {
		DCCP_WARN("length %u for feature %u too large\n", len, feat);
		return -1;
	}

	if (unlikely(val == NULL || len == 0))
		len = repeat_first = 0;
	tot_len = 3 + repeat_first + len;

	if (DCCP_SKB_CB(skb)->dccpd_opt_len + tot_len > DCCP_MAX_OPT_LEN) {
		DCCP_WARN("packet too small for feature %d option!\n", feat);
		return -1;
	}
	DCCP_SKB_CB(skb)->dccpd_opt_len += tot_len;

	to    = skb_push(skb, tot_len);
	*to++ = type;
	*to++ = tot_len;
	*to++ = feat;

	if (repeat_first)
		*to++ = *val;
	if (len)
		memcpy(to, val, len);
	return 0;
}