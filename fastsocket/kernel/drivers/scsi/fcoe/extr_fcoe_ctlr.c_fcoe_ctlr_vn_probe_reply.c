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
struct fcoe_ctlr {scalar_t__ port_id; int state; } ;
struct TYPE_2__ {scalar_t__ port_id; } ;
struct fc_rport_priv {TYPE_1__ ids; } ;

/* Variables and functions */
#define  FIP_ST_VNMP_CLAIM 132 
#define  FIP_ST_VNMP_PROBE1 131 
#define  FIP_ST_VNMP_PROBE2 130 
#define  FIP_ST_VNMP_START 129 
#define  FIP_ST_VNMP_UP 128 
 int /*<<< orphan*/  fcoe_ctlr_vn_restart (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send_claim (struct fcoe_ctlr*) ; 

__attribute__((used)) static void fcoe_ctlr_vn_probe_reply(struct fcoe_ctlr *fip,
				   struct fc_rport_priv *rdata)
{
	if (rdata->ids.port_id != fip->port_id)
		return;
	switch (fip->state) {
	case FIP_ST_VNMP_START:
	case FIP_ST_VNMP_PROBE1:
	case FIP_ST_VNMP_PROBE2:
	case FIP_ST_VNMP_CLAIM:
		fcoe_ctlr_vn_restart(fip);
		break;
	case FIP_ST_VNMP_UP:
		fcoe_ctlr_vn_send_claim(fip);
		break;
	default:
		break;
	}
}