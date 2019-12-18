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
typedef  int /*<<< orphan*/  u32 ;
struct fcoe_rport {int flags; int /*<<< orphan*/  fcoe_len; int /*<<< orphan*/  enode_mac; } ;
struct fcoe_ctlr {int state; TYPE_2__* lp; int /*<<< orphan*/  port_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_name; int /*<<< orphan*/  port_id; } ;
struct fc_rport_priv {TYPE_1__ ids; } ;
struct TYPE_4__ {int /*<<< orphan*/  wwpn; } ;

/* Variables and functions */
 int FIP_FL_REC_OR_P2P ; 
 int /*<<< orphan*/  FIP_SC_VN_CLAIM_REP ; 
 int /*<<< orphan*/  FIP_SC_VN_PROBE_REQ ; 
#define  FIP_ST_VNMP_CLAIM 132 
#define  FIP_ST_VNMP_PROBE1 131 
#define  FIP_ST_VNMP_PROBE2 130 
#define  FIP_ST_VNMP_START 129 
#define  FIP_ST_VNMP_UP 128 
 int /*<<< orphan*/  fcoe_all_vn2vn ; 
 int /*<<< orphan*/  fcoe_ctlr_fcoe_size (struct fcoe_ctlr*) ; 
 struct fcoe_rport* fcoe_ctlr_rport (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_add (struct fcoe_ctlr*,struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_restart (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send (struct fcoe_ctlr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send_claim (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_ctlr_vn_claim_notify(struct fcoe_ctlr *fip,
				      struct fc_rport_priv *new)
{
	struct fcoe_rport *frport = fcoe_ctlr_rport(new);

	if (frport->flags & FIP_FL_REC_OR_P2P) {
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		return;
	}
	switch (fip->state) {
	case FIP_ST_VNMP_START:
	case FIP_ST_VNMP_PROBE1:
	case FIP_ST_VNMP_PROBE2:
		if (new->ids.port_id == fip->port_id)
			fcoe_ctlr_vn_restart(fip);
		break;
	case FIP_ST_VNMP_CLAIM:
	case FIP_ST_VNMP_UP:
		if (new->ids.port_id == fip->port_id) {
			if (new->ids.port_name > fip->lp->wwpn) {
				fcoe_ctlr_vn_restart(fip);
				break;
			}
			fcoe_ctlr_vn_send_claim(fip);
			break;
		}
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_CLAIM_REP, frport->enode_mac,
				  min((u32)frport->fcoe_len,
				      fcoe_ctlr_fcoe_size(fip)));
		fcoe_ctlr_vn_add(fip, new);
		break;
	default:
		break;
	}
}