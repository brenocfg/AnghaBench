#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pairing_bda; scalar_t__ flags; int /*<<< orphan*/  rsp_timer_ent; } ;
typedef  TYPE_1__ tSMP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  L2CA_SetIdleTimeoutByBdAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_LINK_TOUT_MIN ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_cb_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  smp_remove_fixed_channel (TYPE_1__*) ; 

void smp_reset_control_value(tSMP_CB *p_cb)
{
    SMP_TRACE_EVENT("smp_reset_control_value\n");
    btu_stop_timer (&p_cb->rsp_timer_ent);
    p_cb->flags = 0;
    /* set the link idle timer to drop the link when pairing is done
       usually service discovery will follow authentication complete, to avoid
       racing condition for a link down/up, set link idle timer to be
       SMP_LINK_TOUT_MIN to guarantee SMP key exchange */
    L2CA_SetIdleTimeoutByBdAddr(p_cb->pairing_bda, SMP_LINK_TOUT_MIN, BT_TRANSPORT_LE);

    /* We can tell L2CAP to remove the fixed channel (if it has one) */
    smp_remove_fixed_channel(p_cb);
    smp_cb_cleanup(p_cb);
}