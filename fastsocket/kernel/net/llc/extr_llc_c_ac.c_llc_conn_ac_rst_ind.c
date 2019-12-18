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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_sock {int /*<<< orphan*/  n2; int /*<<< orphan*/  retry_count; } ;
struct llc_pdu_un {int dummy; } ;
struct llc_conn_state_ev {int type; int /*<<< orphan*/  ind_prim; int /*<<< orphan*/  reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_2_PDU_CMD_SABME ; 
 int /*<<< orphan*/  LLC_2_PDU_RSP_FRMR ; 
#define  LLC_CONN_EV_TYPE_ACK_TMR 132 
#define  LLC_CONN_EV_TYPE_BUSY_TMR 131 
#define  LLC_CONN_EV_TYPE_PDU 130 
#define  LLC_CONN_EV_TYPE_P_TMR 129 
#define  LLC_CONN_EV_TYPE_REJ_TMR 128 
 int /*<<< orphan*/  LLC_PDU_IS_CMD (struct llc_pdu_un*) ; 
 int /*<<< orphan*/  LLC_PDU_IS_RSP (struct llc_pdu_un*) ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_IS_U (struct llc_pdu_un*) ; 
 int /*<<< orphan*/  LLC_RESET_PRIM ; 
 int /*<<< orphan*/  LLC_RESET_REASON_LOCAL ; 
 int /*<<< orphan*/  LLC_RESET_REASON_REMOTE ; 
 int /*<<< orphan*/  LLC_U_PDU_CMD (struct llc_pdu_un*) ; 
 int /*<<< orphan*/  LLC_U_PDU_RSP (struct llc_pdu_un*) ; 
 struct llc_conn_state_ev* llc_conn_ev (struct sk_buff*) ; 
 struct llc_pdu_un* llc_pdu_un_hdr (struct sk_buff*) ; 
 struct llc_sock* llc_sk (struct sock*) ; 

int llc_conn_ac_rst_ind(struct sock *sk, struct sk_buff *skb)
{
	u8 reason = 0;
	int rc = 1;
	struct llc_conn_state_ev *ev = llc_conn_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);
	struct llc_sock *llc = llc_sk(sk);

	switch (ev->type) {
	case LLC_CONN_EV_TYPE_PDU:
		if (LLC_PDU_IS_RSP(pdu) &&
		    LLC_PDU_TYPE_IS_U(pdu) &&
		    LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_FRMR) {
			reason = LLC_RESET_REASON_LOCAL;
			rc = 0;
		} else if (LLC_PDU_IS_CMD(pdu) &&
			   LLC_PDU_TYPE_IS_U(pdu) &&
			   LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_SABME) {
			reason = LLC_RESET_REASON_REMOTE;
			rc = 0;
		}
		break;
	case LLC_CONN_EV_TYPE_ACK_TMR:
	case LLC_CONN_EV_TYPE_P_TMR:
	case LLC_CONN_EV_TYPE_REJ_TMR:
	case LLC_CONN_EV_TYPE_BUSY_TMR:
		if (llc->retry_count > llc->n2) {
			reason = LLC_RESET_REASON_LOCAL;
			rc = 0;
		}
		break;
	}
	if (!rc) {
		ev->reason   = reason;
		ev->ind_prim = LLC_RESET_PRIM;
	}
	return rc;
}