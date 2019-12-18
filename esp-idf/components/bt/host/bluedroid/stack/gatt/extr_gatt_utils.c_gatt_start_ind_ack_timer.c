#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ param; } ;
struct TYPE_4__ {TYPE_3__ ind_ack_timer_ent; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  scalar_t__ TIMER_PARAM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_ATT_WAIT_FOR_IND_ACK ; 
 int /*<<< orphan*/  GATT_WAIT_FOR_IND_ACK_TOUT ; 
 int /*<<< orphan*/  btu_start_timer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gatt_start_ind_ack_timer(tGATT_TCB *p_tcb)
{
    p_tcb->ind_ack_timer_ent.param  = (TIMER_PARAM_TYPE)p_tcb;
    /* start notification cache timer */
    btu_start_timer (&p_tcb->ind_ack_timer_ent, BTU_TTYPE_ATT_WAIT_FOR_IND_ACK,
                     GATT_WAIT_FOR_IND_ACK_TOUT);

}