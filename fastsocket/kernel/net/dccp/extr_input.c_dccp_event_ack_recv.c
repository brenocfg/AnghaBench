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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/ * dccps_hc_rx_ackvec; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccpd_ack_seq; } ;

/* Variables and functions */
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_ackvec_check_rcv_ackno (int /*<<< orphan*/ *,struct sock*,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static void dccp_event_ack_recv(struct sock *sk, struct sk_buff *skb)
{
	struct dccp_sock *dp = dccp_sk(sk);

	if (dp->dccps_hc_rx_ackvec != NULL)
		dccp_ackvec_check_rcv_ackno(dp->dccps_hc_rx_ackvec, sk,
					    DCCP_SKB_CB(skb)->dccpd_ack_seq);
}