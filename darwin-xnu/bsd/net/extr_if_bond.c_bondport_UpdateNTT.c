#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* lacpdu_ref ;
typedef  TYPE_2__* lacp_actor_partner_tlv_ref ;
typedef  TYPE_3__* ifbond_ref ;
typedef  TYPE_4__* bondport_ref ;
struct TYPE_19__ {scalar_t__ system_priority; scalar_t__ verbose; int /*<<< orphan*/  system; } ;
struct TYPE_18__ {scalar_t__ po_priority; int /*<<< orphan*/  po_actor_state; TYPE_3__* po_bond; } ;
struct TYPE_17__ {scalar_t__ ifb_key; } ;
struct TYPE_16__ {int /*<<< orphan*/  lap_state; int /*<<< orphan*/  lap_system; } ;
struct TYPE_15__ {scalar_t__ la_partner_tlv; } ;

/* Variables and functions */
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bondport_flags_set_ntt (TYPE_4__*) ; 
 scalar_t__ bondport_get_index (TYPE_4__*) ; 
 int /*<<< orphan*/  bondport_get_name (TYPE_4__*) ; 
 TYPE_9__* g_bond ; 
 scalar_t__ lacp_actor_partner_tlv_get_key (TYPE_2__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_port (TYPE_2__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_port_priority (TYPE_2__*) ; 
 scalar_t__ lacp_actor_partner_tlv_get_system_priority (TYPE_2__*) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ updateNTTBits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_UpdateNTT(bondport_ref p, lacpdu_ref lacpdu_p)
{
    ifbond_ref			bond = p->po_bond;
    lacp_actor_partner_tlv_ref	partner;

    /* compare the PDU's Actor information to our Partner state */
    partner = (lacp_actor_partner_tlv_ref)lacpdu_p->la_partner_tlv;
    if ((lacp_actor_partner_tlv_get_port(partner) != bondport_get_index(p))
	|| lacp_actor_partner_tlv_get_port_priority(partner) != p->po_priority
	|| bcmp(partner->lap_system, &g_bond->system, sizeof(g_bond->system))
	|| (lacp_actor_partner_tlv_get_system_priority(partner) 
	    != g_bond->system_priority)
	|| lacp_actor_partner_tlv_get_key(partner) != bond->ifb_key
	|| (updateNTTBits(partner->lap_state) 
	    != updateNTTBits(p->po_actor_state))) {
	bondport_flags_set_ntt(p);
	if (g_bond->verbose) {
	    timestamp_printf("[%s] updateNTT: Need To Transmit\n",
			     bondport_get_name(p));
	}
    }
    return;
}