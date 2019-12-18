#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_1__* partner_state_ref ;
typedef  TYPE_2__* lacpdu_ref ;
typedef  int /*<<< orphan*/ * lacp_system_ref ;
typedef  TYPE_3__* lacp_actor_partner_tlv_ref ;
typedef  TYPE_4__* ifbond_ref ;
typedef  TYPE_5__* bondport_ref ;
struct TYPE_23__ {scalar_t__ li_key; scalar_t__ li_system_priority; int /*<<< orphan*/  li_system; } ;
struct TYPE_18__ {void* ps_state; scalar_t__ ps_port_priority; scalar_t__ ps_port; TYPE_6__ ps_lag_info; } ;
struct TYPE_22__ {scalar_t__ po_priority; void* po_actor_state; TYPE_1__ po_partner_state; TYPE_4__* po_bond; } ;
struct TYPE_21__ {scalar_t__ ifb_key; } ;
struct TYPE_20__ {void* lap_state; scalar_t__ lap_system; } ;
struct TYPE_19__ {scalar_t__ la_partner_tlv; scalar_t__ la_actor_tlv; } ;
struct TYPE_17__ {scalar_t__ system_priority; scalar_t__ verbose; int /*<<< orphan*/  system; } ;
typedef  TYPE_6__* LAG_info_ref ;

/* Variables and functions */
 scalar_t__ bcmp (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bondport_assign_to_LAG (TYPE_5__*) ; 
 scalar_t__ bondport_get_index (TYPE_5__*) ; 
 int /*<<< orphan*/  bondport_get_name (TYPE_5__*) ; 
 TYPE_11__* g_bond ; 
 scalar_t__ lacp_actor_partner_state_active_lacp (void*) ; 
 scalar_t__ lacp_actor_partner_state_aggregatable (void*) ; 
 scalar_t__ lacp_actor_partner_state_in_sync (void*) ; 
 void* lacp_actor_partner_state_set_in_sync (void*) ; 
 void* lacp_actor_partner_state_set_not_defaulted (void*) ; 
 void* lacp_actor_partner_state_set_out_of_sync (void*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_key (TYPE_3__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_port (TYPE_3__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_port_priority (TYPE_3__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_system_priority (TYPE_3__*) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_RecordPDU(bondport_ref p, lacpdu_ref lacpdu_p)
{
    lacp_actor_partner_tlv_ref	actor;
    ifbond_ref			bond = p->po_bond;
    int				lacp_maintain = 0;
    partner_state_ref		ps;
    lacp_actor_partner_tlv_ref	partner;
    LAG_info_ref		ps_li;

    /* copy the PDU's Actor information into our Partner state */
    actor = (lacp_actor_partner_tlv_ref)lacpdu_p->la_actor_tlv;
    ps = &p->po_partner_state;
    ps_li = &ps->ps_lag_info;
    ps->ps_port = lacp_actor_partner_tlv_get_port(actor);
    ps->ps_port_priority = lacp_actor_partner_tlv_get_port_priority(actor);
    ps_li->li_system = *((lacp_system_ref)actor->lap_system);
    ps_li->li_system_priority 
	= lacp_actor_partner_tlv_get_system_priority(actor);
    ps_li->li_key = lacp_actor_partner_tlv_get_key(actor);
    ps->ps_state = lacp_actor_partner_state_set_out_of_sync(actor->lap_state);
    p->po_actor_state 
	= lacp_actor_partner_state_set_not_defaulted(p->po_actor_state);

    /* compare the PDU's Partner information to our own information */
    partner = (lacp_actor_partner_tlv_ref)lacpdu_p->la_partner_tlv;

    if (lacp_actor_partner_state_active_lacp(ps->ps_state)
	|| (lacp_actor_partner_state_active_lacp(p->po_actor_state)
	    && lacp_actor_partner_state_active_lacp(partner->lap_state))) {
	if (g_bond->verbose) {
	    timestamp_printf("[%s] recordPDU: LACP will maintain\n",
			     bondport_get_name(p));
	}
	lacp_maintain = 1;
    }
    if ((lacp_actor_partner_tlv_get_port(partner) 
	 == bondport_get_index(p))
	&& lacp_actor_partner_tlv_get_port_priority(partner) == p->po_priority
	&& bcmp(partner->lap_system, &g_bond->system, 
		sizeof(g_bond->system)) == 0
	&& (lacp_actor_partner_tlv_get_system_priority(partner) 
	    == g_bond->system_priority)
	&& lacp_actor_partner_tlv_get_key(partner) == bond->ifb_key
	&& (lacp_actor_partner_state_aggregatable(partner->lap_state)
	    == lacp_actor_partner_state_aggregatable(p->po_actor_state))
	&& lacp_actor_partner_state_in_sync(actor->lap_state)
	&& lacp_maintain) {
	ps->ps_state = lacp_actor_partner_state_set_in_sync(ps->ps_state);
	if (g_bond->verbose) {
	    timestamp_printf("[%s] recordPDU: LACP partner in sync\n",
			     bondport_get_name(p));
	}
    }
    else if (lacp_actor_partner_state_aggregatable(actor->lap_state) == 0
	     && lacp_actor_partner_state_in_sync(actor->lap_state)
	     && lacp_maintain) {
	ps->ps_state = lacp_actor_partner_state_set_in_sync(ps->ps_state);
	if (g_bond->verbose) {
	    timestamp_printf("[%s] recordPDU: LACP partner in sync (ind)\n",
			     bondport_get_name(p));
	}
    }
    bondport_assign_to_LAG(p);
    return;
}