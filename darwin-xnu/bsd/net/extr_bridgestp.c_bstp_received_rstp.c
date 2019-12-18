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
struct mbuf {scalar_t__ m_len; } ;
struct bstp_tbpdu {scalar_t__ tbu_bpdutype; } ;
struct bstp_state {int dummy; } ;
struct bstp_config_unit {int dummy; } ;
struct bstp_port {struct bstp_config_unit bp_msg_cu; } ;
struct bstp_cbpdu {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSTP_BPDU_RSTP_LEN ; 
 scalar_t__ BSTP_MSGTYPE_RSTP ; 
 int /*<<< orphan*/  bstp_decode_bpdu (struct bstp_port*,struct bstp_cbpdu*,struct bstp_config_unit*) ; 
 int /*<<< orphan*/  bstp_received_bpdu (struct bstp_state*,struct bstp_port*,struct bstp_config_unit*) ; 
 int /*<<< orphan*/  caddr_t ; 
 struct mbuf* m_pullup (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct bstp_cbpdu*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_received_rstp(struct bstp_state *bs, struct bstp_port *bp,
    struct mbuf **mp, struct bstp_tbpdu *tpdu)
{
	struct bstp_cbpdu cpdu;
	struct bstp_config_unit *cu = &bp->bp_msg_cu;

	if (tpdu->tbu_bpdutype != BSTP_MSGTYPE_RSTP)
		return;

	if ((*mp)->m_len < BSTP_BPDU_RSTP_LEN &&
	    (*mp = m_pullup(*mp, BSTP_BPDU_RSTP_LEN)) == NULL)
		return;
	memcpy(&cpdu, mtod(*mp, caddr_t), BSTP_BPDU_RSTP_LEN);

	bstp_decode_bpdu(bp, &cpdu, cu);
	bstp_received_bpdu(bs, bp, cu);
}