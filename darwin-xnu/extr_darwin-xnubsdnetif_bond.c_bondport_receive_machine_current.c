#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__* partner_state_ref ;
typedef  int /*<<< orphan*/  devtimer_timeout_func ;
typedef  TYPE_2__* bondport_ref ;
struct TYPE_13__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_11__ {int /*<<< orphan*/  ps_state; } ;
struct TYPE_12__ {int /*<<< orphan*/  po_current_while_timer; TYPE_1__ po_partner_state; int /*<<< orphan*/  po_actor_state; int /*<<< orphan*/  po_receive_state; } ;
typedef  int LAEvent ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_LONG_TIMEOUT_TIME ; 
 int /*<<< orphan*/  LACP_SHORT_TIMEOUT_TIME ; 
#define  LAEventPacket 129 
 int /*<<< orphan*/  LAEventStart ; 
#define  LAEventTimeout 128 
 int /*<<< orphan*/  ReceiveState_CURRENT ; 
 int /*<<< orphan*/  bondport_RecordPDU (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  bondport_UpdateNTT (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  bondport_UpdateSelected (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  bondport_assign_to_LAG (TYPE_2__*) ; 
 int /*<<< orphan*/  bondport_get_name (TYPE_2__*) ; 
 int /*<<< orphan*/  bondport_receive_machine_expired (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devtimer_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devtimer_set_relative (int /*<<< orphan*/ ,struct timeval,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_3__* g_bond ; 
 int /*<<< orphan*/  lacp_actor_partner_state_set_not_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_actor_partner_state_short_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_receive_machine_current(bondport_ref p, LAEvent event,
				 void * event_data)
{
    partner_state_ref	ps;
    struct timeval	tv;

    switch (event) {
    case LAEventPacket:
	devtimer_cancel(p->po_current_while_timer);
	if (g_bond->verbose) {
	    timestamp_printf("[%s] Receive CURRENT\n",
			     bondport_get_name(p));
	}
	p->po_receive_state = ReceiveState_CURRENT;
	bondport_UpdateSelected(p, event_data);
	bondport_UpdateNTT(p, event_data);
	bondport_RecordPDU(p, event_data);
	p->po_actor_state
	    = lacp_actor_partner_state_set_not_expired(p->po_actor_state);
	bondport_assign_to_LAG(p);
	/* start current_while timer */
	ps = &p->po_partner_state;
	if (lacp_actor_partner_state_short_timeout(ps->ps_state)) {
	    tv.tv_sec = LACP_SHORT_TIMEOUT_TIME;
	}
	else {
	    tv.tv_sec = LACP_LONG_TIMEOUT_TIME;
	}
	tv.tv_usec = 0;
	devtimer_set_relative(p->po_current_while_timer, tv,
			      (devtimer_timeout_func)
			      bondport_receive_machine_current,
			      (void *)LAEventTimeout, NULL);
	break;
    case LAEventTimeout:
	bondport_receive_machine_expired(p, LAEventStart, NULL);
	break;
    default:
	break;
    }
    return;
}