#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ind_count; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_6__ {scalar_t__ param; } ;
typedef  TYPE_2__ TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_HANDLE_VALUE_CONF ; 
 int /*<<< orphan*/  GATT_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  attp_send_cl_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gatt_ind_ack_timeout(TIMER_LIST_ENT *p_tle)
{
    tGATT_TCB *p_tcb = (tGATT_TCB *)p_tle->param;

    GATT_TRACE_WARNING("gatt_ind_ack_timeout send ack now");

    if (p_tcb != NULL) {
        p_tcb->ind_count = 0;
    }

    attp_send_cl_msg(((tGATT_TCB *)p_tle->param), 0, GATT_HANDLE_VALUE_CONF, NULL);
}