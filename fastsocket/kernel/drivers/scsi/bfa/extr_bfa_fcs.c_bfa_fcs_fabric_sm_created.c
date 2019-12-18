#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_s {int dummy; } ;
struct TYPE_5__ {int pwwn; } ;
struct TYPE_7__ {int /*<<< orphan*/  pid; TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_2__* fcs; TYPE_4__ bport; int /*<<< orphan*/  fab_type; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;
struct TYPE_6__ {struct bfa_s* bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_LOOP ; 
#define  BFA_FCS_FABRIC_SM_DELETE 131 
#define  BFA_FCS_FABRIC_SM_LINK_DOWN 130 
#define  BFA_FCS_FABRIC_SM_LINK_UP 129 
#define  BFA_FCS_FABRIC_SM_START 128 
 int /*<<< orphan*/  BFA_PORT_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  bfa_fcport_get_myalpa (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcport_get_topology (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcport_is_linkup (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_delete (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_login (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_set_opertype (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_deleting ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_flogi ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_linkdown ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_online ; 
 int /*<<< orphan*/  bfa_fcs_lport_online (TYPE_4__*) ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int) ; 

__attribute__((used)) static void
bfa_fcs_fabric_sm_created(struct bfa_fcs_fabric_s *fabric,
			  enum bfa_fcs_fabric_event event)
{
	struct bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_START:
		if (!bfa_fcport_is_linkup(fabric->fcs->bfa)) {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkdown);
			break;
		}
		if (bfa_fcport_get_topology(bfa) ==
				BFA_PORT_TOPOLOGY_LOOP) {
			fabric->fab_type = BFA_FCS_FABRIC_LOOP;
			fabric->bport.pid = bfa_fcport_get_myalpa(bfa);
			fabric->bport.pid = bfa_hton3b(fabric->bport.pid);
			bfa_sm_set_state(fabric,
					bfa_fcs_fabric_sm_online);
			bfa_fcs_fabric_set_opertype(fabric);
			bfa_fcs_lport_online(&fabric->bport);
		} else {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi);
			bfa_fcs_fabric_login(fabric);
		}
		break;

	case BFA_FCS_FABRIC_SM_LINK_UP:
	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		break;

	case BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}