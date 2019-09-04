#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* partner_state_ref ;
typedef  TYPE_2__* bondport_ref ;
struct TYPE_8__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_6__ {int /*<<< orphan*/  ps_state; } ;
struct TYPE_7__ {int po_receive_state; int /*<<< orphan*/ * po_lag; int /*<<< orphan*/  po_actor_state; TYPE_1__ po_partner_state; } ;

/* Variables and functions */
#define  ReceiveState_CURRENT 129 
#define  ReceiveState_EXPIRED 128 
 int /*<<< orphan*/  bondport_get_name (TYPE_2__*) ; 
 TYPE_3__* g_bond ; 
 scalar_t__ lacp_actor_partner_state_aggregatable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bondport_aggregatable(bondport_ref p)
{
    partner_state_ref 	ps = &p->po_partner_state;

    if (lacp_actor_partner_state_aggregatable(p->po_actor_state) == 0
	|| lacp_actor_partner_state_aggregatable(ps->ps_state) == 0) {
	/* we and/or our partner are individual */
	return (0);
    }
    if (p->po_lag == NULL) {
	return (0);
    }
    switch (p->po_receive_state) {
    default:
	if (g_bond->verbose) {
	    timestamp_printf("[%s] Port is not selectable\n", 
			     bondport_get_name(p));
	}
	return (0);
    case ReceiveState_CURRENT:
    case ReceiveState_EXPIRED:
	break;
    }
    return (1);
}