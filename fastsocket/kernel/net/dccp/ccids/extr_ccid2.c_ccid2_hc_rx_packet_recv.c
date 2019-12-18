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
struct dccp_sock {int /*<<< orphan*/  dccps_r_ack_ratio; } ;
struct ccid2_hc_rx_sock {int /*<<< orphan*/  ccid2hcrx_data; } ;
struct TYPE_2__ {int dccpd_type; } ;

/* Variables and functions */
#define  DCCP_PKT_DATA 129 
#define  DCCP_PKT_DATAACK 128 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 struct ccid2_hc_rx_sock* ccid2_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static void ccid2_hc_rx_packet_recv(struct sock *sk, struct sk_buff *skb)
{
	const struct dccp_sock *dp = dccp_sk(sk);
	struct ccid2_hc_rx_sock *hcrx = ccid2_hc_rx_sk(sk);

	switch (DCCP_SKB_CB(skb)->dccpd_type) {
	case DCCP_PKT_DATA:
	case DCCP_PKT_DATAACK:
		hcrx->ccid2hcrx_data++;
		if (hcrx->ccid2hcrx_data >= dp->dccps_r_ack_ratio) {
			dccp_send_ack(sk);
			hcrx->ccid2hcrx_data = 0;
		}
		break;
	}
}