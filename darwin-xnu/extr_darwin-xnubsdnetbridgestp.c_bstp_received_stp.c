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
struct mbuf {int /*<<< orphan*/  m_len; } ;
struct bstp_tcn_unit {int tu_message_type; } ;
struct bstp_tbpdu {int tbu_bpdutype; } ;
struct bstp_state {int dummy; } ;
struct bstp_config_unit {int dummy; } ;
struct bstp_port {struct bstp_config_unit bp_msg_cu; } ;
struct bstp_cbpdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_BPDU_STP_LEN ; 
#define  BSTP_MSGTYPE_CFG 129 
#define  BSTP_MSGTYPE_TCN 128 
 int /*<<< orphan*/  bstp_decode_bpdu (struct bstp_port*,struct bstp_cbpdu*,struct bstp_config_unit*) ; 
 int /*<<< orphan*/  bstp_received_bpdu (struct bstp_state*,struct bstp_port*,struct bstp_config_unit*) ; 
 int /*<<< orphan*/  bstp_received_tcn (struct bstp_state*,struct bstp_port*,struct bstp_tcn_unit*) ; 
 int /*<<< orphan*/  caddr_t ; 
 struct mbuf* m_pullup (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct bstp_cbpdu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_received_stp(struct bstp_state *bs, struct bstp_port *bp,
    struct mbuf **mp, struct bstp_tbpdu *tpdu)
{
	struct bstp_cbpdu cpdu;
	struct bstp_config_unit *cu = &bp->bp_msg_cu;
	struct bstp_tcn_unit tu;

	switch (tpdu->tbu_bpdutype) {
	case BSTP_MSGTYPE_TCN:
		tu.tu_message_type = tpdu->tbu_bpdutype;
		bstp_received_tcn(bs, bp, &tu);
		break;
	case BSTP_MSGTYPE_CFG:
		if ((*mp)->m_len < BSTP_BPDU_STP_LEN &&
		    (*mp = m_pullup(*mp, BSTP_BPDU_STP_LEN)) == NULL)
			return;
		memcpy(&cpdu, mtod(*mp, caddr_t), BSTP_BPDU_STP_LEN);

		bstp_decode_bpdu(bp, &cpdu, cu);
		bstp_received_bpdu(bs, bp, cu);
		break;
	}
}