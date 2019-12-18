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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_sn {int dummy; } ;

/* Variables and functions */
 scalar_t__ LLC_2_PDU_CMD_REJ ; 
 scalar_t__ LLC_PDU_IS_CMD (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_S (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_S_PDU_CMD (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_S_PF_IS_0 (struct llc_pdu_sn const*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 

int llc_conn_ev_rx_rej_cmd_pbit_set_0(struct sock *sk, struct sk_buff *skb)
{
	const struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	return LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_S(pdu) &&
	       LLC_S_PF_IS_0(pdu) &&
	       LLC_S_PDU_CMD(pdu) == LLC_2_PDU_CMD_REJ ? 0 : 1;
}