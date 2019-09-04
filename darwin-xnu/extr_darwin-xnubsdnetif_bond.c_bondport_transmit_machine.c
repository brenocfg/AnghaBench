#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__* partner_state_ref ;
typedef  int /*<<< orphan*/ * packet_buffer_ref ;
typedef  TYPE_3__* lacpdu_ref ;
typedef  int /*<<< orphan*/ * lacp_system_ref ;
typedef  TYPE_4__* lacp_collector_tlv_ref ;
typedef  TYPE_5__* lacp_actor_partner_tlv_ref ;
typedef  int /*<<< orphan*/  devtimer_timeout_func ;
typedef  TYPE_6__* bondport_ref ;
struct TYPE_28__ {int /*<<< orphan*/  li_key; int /*<<< orphan*/  li_system_priority; int /*<<< orphan*/  li_system; } ;
struct TYPE_23__ {int /*<<< orphan*/  ps_state; int /*<<< orphan*/  ps_port_priority; int /*<<< orphan*/  ps_port; TYPE_7__ ps_lag_info; } ;
struct TYPE_27__ {int po_n_transmit; TYPE_2__ po_partner_state; int /*<<< orphan*/  po_actor_state; TYPE_1__* po_bond; int /*<<< orphan*/  po_priority; int /*<<< orphan*/  po_transmit_timer; int /*<<< orphan*/  po_periodic_interval; } ;
struct TYPE_26__ {int /*<<< orphan*/  lap_state; int /*<<< orphan*/  lap_system; int /*<<< orphan*/  lap_length; int /*<<< orphan*/  lap_tlv_type; } ;
struct TYPE_25__ {int /*<<< orphan*/  lac_length; int /*<<< orphan*/  lac_tlv_type; } ;
struct TYPE_24__ {int /*<<< orphan*/  la_collector_tlv; int /*<<< orphan*/  la_partner_tlv; int /*<<< orphan*/  la_actor_tlv; int /*<<< orphan*/  la_version; int /*<<< orphan*/  la_subtype; } ;
struct TYPE_22__ {int /*<<< orphan*/  ifb_key; } ;
struct TYPE_21__ {int /*<<< orphan*/  verbose; int /*<<< orphan*/  system_priority; int /*<<< orphan*/  system; } ;
typedef  TYPE_7__* LAG_info_ref ;
typedef  int LAEvent ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE8023AD_SLOW_PROTO_SUBTYPE_LACP ; 
 int /*<<< orphan*/  LACPDU_ACTOR_TLV_LENGTH ; 
 int /*<<< orphan*/  LACPDU_COLLECTOR_TLV_LENGTH ; 
 int /*<<< orphan*/  LACPDU_PARTNER_TLV_LENGTH ; 
 int /*<<< orphan*/  LACPDU_TLV_TYPE_ACTOR ; 
 int /*<<< orphan*/  LACPDU_TLV_TYPE_COLLECTOR ; 
 int /*<<< orphan*/  LACPDU_TLV_TYPE_PARTNER ; 
 int /*<<< orphan*/  LACPDU_VERSION_1 ; 
#define  LAEventStart 129 
#define  LAEventTimeout 128 
 void* TRANSMIT_MACHINE_TX_IMMEDIATE ; 
 int /*<<< orphan*/  bondport_can_transmit (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bondport_flags_clear_ntt (TYPE_6__*) ; 
 int /*<<< orphan*/  bondport_flags_ntt (TYPE_6__*) ; 
 int /*<<< orphan*/  bondport_get_index (TYPE_6__*) ; 
 char* bondport_get_name (TYPE_6__*) ; 
 int /*<<< orphan*/  bondport_slow_proto_transmit (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  devtimer_current_secs () ; 
 int /*<<< orphan*/  devtimer_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devtimer_set_absolute (int /*<<< orphan*/ ,struct timeval,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_12__* g_bond ; 
 int /*<<< orphan*/  lacp_actor_partner_tlv_set_key (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_actor_partner_tlv_set_port (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_actor_partner_tlv_set_port_priority (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_actor_partner_tlv_set_system_priority (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * packet_buffer_allocate (int) ; 
 int /*<<< orphan*/  packet_buffer_byteptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  timestamp_printf (char*,char*,...) ; 

__attribute__((used)) static void
bondport_transmit_machine(bondport_ref p, LAEvent event,
			  void * event_data)
{
    lacp_actor_partner_tlv_ref	aptlv;
    lacp_collector_tlv_ref	ctlv;
    struct timeval		next_tick_time = {0, 0};
    lacpdu_ref		out_lacpdu_p;
    packet_buffer_ref		pkt;
    partner_state_ref		ps;
    LAG_info_ref		ps_li;

    switch (event) {
    case LAEventTimeout:
    case LAEventStart:
	if (p->po_periodic_interval == 0 || bondport_flags_ntt(p) == 0) {
	    break;
	}
	if (event_data == TRANSMIT_MACHINE_TX_IMMEDIATE) {
	    /* we're going away, transmit the packet no matter what */
	}
	else if (bondport_can_transmit(p, devtimer_current_secs(),
				       &next_tick_time.tv_sec) == 0) {
	    if (devtimer_enabled(p->po_transmit_timer)) {
		if (g_bond->verbose > 0) {
		    timestamp_printf("[%s] Transmit Timer Already Set\n",
				     bondport_get_name(p));
		}
	    }
	    else {
		devtimer_set_absolute(p->po_transmit_timer, next_tick_time,
				      (devtimer_timeout_func)
				      bondport_transmit_machine,
				      (void *)LAEventTimeout, NULL);
		if (g_bond->verbose > 0) {
		    timestamp_printf("[%s] Transmit Timer Deadline %d secs\n",
				     bondport_get_name(p),
				     (int)next_tick_time.tv_sec);
		}
	    }
	    break;
	}
	if (g_bond->verbose > 0) {
	    if (event == LAEventTimeout) {
		timestamp_printf("[%s] Transmit Timer Complete\n",
				 bondport_get_name(p));
	    }
	}
	pkt = packet_buffer_allocate(sizeof(*out_lacpdu_p));
	if (pkt == NULL) {
	    printf("[%s] Transmit: failed to allocate packet buffer\n",
		   bondport_get_name(p));
	    break;
	}
	out_lacpdu_p = (lacpdu_ref)packet_buffer_byteptr(pkt);
	bzero(out_lacpdu_p, sizeof(*out_lacpdu_p));
	out_lacpdu_p->la_subtype = IEEE8023AD_SLOW_PROTO_SUBTYPE_LACP;
	out_lacpdu_p->la_version = LACPDU_VERSION_1;

	/* Actor */
	aptlv = (lacp_actor_partner_tlv_ref)out_lacpdu_p->la_actor_tlv;
	aptlv->lap_tlv_type = LACPDU_TLV_TYPE_ACTOR;
	aptlv->lap_length = LACPDU_ACTOR_TLV_LENGTH;
	*((lacp_system_ref)aptlv->lap_system) = g_bond->system;
	lacp_actor_partner_tlv_set_system_priority(aptlv, 
						   g_bond->system_priority);
	lacp_actor_partner_tlv_set_port_priority(aptlv, p->po_priority);
	lacp_actor_partner_tlv_set_port(aptlv, bondport_get_index(p));
	lacp_actor_partner_tlv_set_key(aptlv, p->po_bond->ifb_key);
	aptlv->lap_state = p->po_actor_state;

	/* Partner */
	aptlv = (lacp_actor_partner_tlv_ref)out_lacpdu_p->la_partner_tlv;
	aptlv->lap_tlv_type = LACPDU_TLV_TYPE_PARTNER;
	aptlv->lap_length = LACPDU_PARTNER_TLV_LENGTH;
	ps = &p->po_partner_state;
	ps_li = &ps->ps_lag_info;
	lacp_actor_partner_tlv_set_port(aptlv, ps->ps_port);
	lacp_actor_partner_tlv_set_port_priority(aptlv, ps->ps_port_priority);
	*((lacp_system_ref)aptlv->lap_system) = ps_li->li_system;
	lacp_actor_partner_tlv_set_system_priority(aptlv, 
						   ps_li->li_system_priority);
	lacp_actor_partner_tlv_set_key(aptlv, ps_li->li_key);
	aptlv->lap_state = ps->ps_state;

	/* Collector */
	ctlv = (lacp_collector_tlv_ref)out_lacpdu_p->la_collector_tlv;
	ctlv->lac_tlv_type = LACPDU_TLV_TYPE_COLLECTOR;
	ctlv->lac_length = LACPDU_COLLECTOR_TLV_LENGTH;

	bondport_slow_proto_transmit(p, pkt);
	bondport_flags_clear_ntt(p);
	if (g_bond->verbose > 0) {
	    timestamp_printf("[%s] Transmit Packet %d\n",
			     bondport_get_name(p), p->po_n_transmit);
	}
	break;
    default:
	break;
    }
    return;
}