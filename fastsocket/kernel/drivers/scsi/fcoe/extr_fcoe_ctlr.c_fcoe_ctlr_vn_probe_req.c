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
struct fcoe_rport {int flags; int /*<<< orphan*/  enode_mac; } ;
struct fcoe_ctlr {scalar_t__ port_id; int state; TYPE_2__* lp; } ;
struct TYPE_3__ {scalar_t__ port_id; int /*<<< orphan*/  port_name; } ;
struct fc_rport_priv {TYPE_1__ ids; } ;
struct TYPE_4__ {int /*<<< orphan*/  wwpn; } ;

/* Variables and functions */
 int FIP_FL_REC_OR_P2P ; 
 int /*<<< orphan*/  FIP_SC_VN_PROBE_REP ; 
#define  FIP_ST_VNMP_CLAIM 132 
#define  FIP_ST_VNMP_PROBE1 131 
#define  FIP_ST_VNMP_PROBE2 130 
#define  FIP_ST_VNMP_START 129 
#define  FIP_ST_VNMP_UP 128 
 struct fcoe_rport* fcoe_ctlr_rport (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_restart (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send (struct fcoe_ctlr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_ctlr_vn_probe_req(struct fcoe_ctlr *fip,
				   struct fc_rport_priv *rdata)
{
	struct fcoe_rport *frport = fcoe_ctlr_rport(rdata);

	if (rdata->ids.port_id != fip->port_id)
		return;

	switch (fip->state) {
	case FIP_ST_VNMP_CLAIM:
	case FIP_ST_VNMP_UP:
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REP,
				  frport->enode_mac, 0);
		break;
	case FIP_ST_VNMP_PROBE1:
	case FIP_ST_VNMP_PROBE2:
		/*
		 * Decide whether to reply to the Probe.
		 * Our selected address is never a "recorded" one, so
		 * only reply if our WWPN is greater and the
		 * Probe's REC bit is not set.
		 * If we don't reply, we will change our address.
		 */
		if (fip->lp->wwpn > rdata->ids.port_name &&
		    !(frport->flags & FIP_FL_REC_OR_P2P)) {
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REP,
					  frport->enode_mac, 0);
			break;
		}
		/* fall through */
	case FIP_ST_VNMP_START:
		fcoe_ctlr_vn_restart(fip);
		break;
	default:
		break;
	}
}