#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ param; } ;
struct TYPE_4__ {scalar_t__ operation; scalar_t__ op_subtype; TYPE_3__ rsp_timer_ent; } ;
typedef  TYPE_1__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  size_t UINT16 ;
struct TYPE_5__ {TYPE_1__* clcb; } ;
typedef  scalar_t__ TIMER_PARAM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_ATT_WAIT_FOR_RSP ; 
 scalar_t__ GATTC_OPTYPE_DISCOVERY ; 
 scalar_t__ GATT_DISC_SRVC_ALL ; 
 int /*<<< orphan*/  GATT_WAIT_FOR_DISC_RSP_TOUT ; 
 int /*<<< orphan*/  GATT_WAIT_FOR_RSP_TOUT ; 
 int /*<<< orphan*/  btu_start_timer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ gatt_cb ; 

void gatt_start_rsp_timer(UINT16 clcb_idx)
{
    tGATT_CLCB *p_clcb = &gatt_cb.clcb[clcb_idx];
    UINT32 timeout = GATT_WAIT_FOR_RSP_TOUT;
    p_clcb->rsp_timer_ent.param  = (TIMER_PARAM_TYPE)p_clcb;
    if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY &&
            p_clcb->op_subtype == GATT_DISC_SRVC_ALL) {
        timeout = GATT_WAIT_FOR_DISC_RSP_TOUT;
    }
    btu_start_timer (&p_clcb->rsp_timer_ent, BTU_TTYPE_ATT_WAIT_FOR_RSP,
                     timeout);
}