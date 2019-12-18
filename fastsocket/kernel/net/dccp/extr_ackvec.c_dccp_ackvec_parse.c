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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_hc_rx_ackvec; } ;

/* Variables and functions */
 scalar_t__ const DCCP_SINGLE_OPT_MAXLEN ; 
 int /*<<< orphan*/  dccp_ackvec_check_rcv_ackvector (int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ *,scalar_t__ const,scalar_t__ const*) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 

int dccp_ackvec_parse(struct sock *sk, const struct sk_buff *skb,
		      u64 *ackno, const u8 opt, const u8 *value, const u8 len)
{
	if (len > DCCP_SINGLE_OPT_MAXLEN)
		return -1;

	/* dccp_ackvector_print(DCCP_SKB_CB(skb)->dccpd_ack_seq, value, len); */
	dccp_ackvec_check_rcv_ackvector(dccp_sk(sk)->dccps_hc_rx_ackvec, sk,
					ackno, len, value);
	return 0;
}