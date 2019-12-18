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
struct llc_pdu_sn {int dummy; } ;
struct TYPE_2__ {scalar_t__ vR; } ;

/* Variables and functions */
 scalar_t__ LLC_I_GET_NS (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_I_PF_IS_0 (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_PDU_IS_CMD (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_I (struct llc_pdu_sn const*) ; 
 scalar_t__ llc_conn_space (struct sock*,struct sk_buff*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 TYPE_1__* llc_sk (struct sock*) ; 

int llc_conn_ev_rx_i_cmd_pbit_set_0(struct sock *sk, struct sk_buff *skb)
{
	const struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	return llc_conn_space(sk, skb) &&
	       LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_0(pdu) &&
	       LLC_I_GET_NS(pdu) == llc_sk(sk)->vR ? 0 : 1;
}