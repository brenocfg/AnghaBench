#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* partner_state_ref ;
typedef  TYPE_2__* lacpdu_ref ;
typedef  TYPE_3__* lacp_actor_partner_tlv_ref ;
typedef  TYPE_4__* bondport_ref ;
struct TYPE_20__ {scalar_t__ li_system_priority; scalar_t__ li_key; int /*<<< orphan*/  li_system; } ;
struct TYPE_16__ {scalar_t__ ps_port; scalar_t__ ps_port_priority; int /*<<< orphan*/  ps_state; TYPE_5__ ps_lag_info; } ;
struct TYPE_19__ {TYPE_1__ po_partner_state; } ;
struct TYPE_18__ {int /*<<< orphan*/  lap_state; int /*<<< orphan*/  lap_system; } ;
struct TYPE_17__ {scalar_t__ la_actor_tlv; } ;
struct TYPE_15__ {scalar_t__ verbose; } ;
typedef  TYPE_5__* LAG_info_ref ;

/* Variables and functions */
 int /*<<< orphan*/  SelectedState_UNSELECTED ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bondport_get_name (TYPE_4__*) ; 
 int /*<<< orphan*/  bondport_set_selected (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* g_bond ; 
 scalar_t__ lacp_actor_partner_state_aggregatable (int /*<<< orphan*/ ) ; 
 scalar_t__ lacp_actor_partner_tlv_get_key (TYPE_3__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_port (TYPE_3__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_port_priority (TYPE_3__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_system_priority (TYPE_3__*) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_UpdateSelected(bondport_ref p, lacpdu_ref lacpdu_p)
{
    lacp_actor_partner_tlv_ref	actor;
    partner_state_ref		ps;
    LAG_info_ref		ps_li;

    /* compare the PDU's Actor information to our Partner state */
    actor = (lacp_actor_partner_tlv_ref)lacpdu_p->la_actor_tlv;
    ps = &p->po_partner_state;
    ps_li = &ps->ps_lag_info;
    if (lacp_actor_partner_tlv_get_port(actor) != ps->ps_port
	|| (lacp_actor_partner_tlv_get_port_priority(actor)
	    != ps->ps_port_priority)
	|| bcmp(actor->lap_system, &ps_li->li_system, sizeof(ps_li->li_system))
	|| (lacp_actor_partner_tlv_get_system_priority(actor) 
	    != ps_li->li_system_priority)
	|| (lacp_actor_partner_tlv_get_key(actor) != ps_li->li_key)
	|| (lacp_actor_partner_state_aggregatable(actor->lap_state)
	    != lacp_actor_partner_state_aggregatable(ps->ps_state))) {
	bondport_set_selected(p, SelectedState_UNSELECTED);
	if (g_bond->verbose) {
	    timestamp_printf("[%s] updateSelected UNSELECTED\n",
			     bondport_get_name(p));
	}
    }
    return;
}