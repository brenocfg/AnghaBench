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
struct bfa_fcs_lport_scn_s {TYPE_1__* port; int /*<<< orphan*/  timer; } ;
typedef  enum port_scn_event { ____Placeholder_port_scn_event } port_scn_event ;
struct TYPE_2__ {int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
#define  SCNSM_EVENT_PORT_OFFLINE 129 
#define  SCNSM_EVENT_TIMEOUT 128 
 int /*<<< orphan*/  bfa_fcs_lport_scn_send_scr (struct bfa_fcs_lport_scn_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_sm_sending_scr ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_scn_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_fcs_lport_scn_sm_scr_retry(struct bfa_fcs_lport_scn_s *scn,
				enum port_scn_event event)
{
	switch (event) {
	case SCNSM_EVENT_TIMEOUT:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_sending_scr);
		bfa_fcs_lport_scn_send_scr(scn, NULL);
		break;

	case SCNSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_offline);
		bfa_timer_stop(&scn->timer);
		break;

	default:
		bfa_sm_fault(scn->port->fcs, event);
	}
}