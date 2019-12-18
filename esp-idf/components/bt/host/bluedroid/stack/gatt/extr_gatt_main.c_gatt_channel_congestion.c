#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tcb_idx; } ;
typedef  TYPE_2__ tGATT_TCB ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_congestion_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_1__ app_cb; int /*<<< orphan*/  gatt_if; scalar_t__ in_use; } ;
typedef  TYPE_3__ tGATT_REG ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_10__ {TYPE_3__* cl_rcb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_CREATE_CONN_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_MAX_APPS ; 
 TYPE_6__ gatt_cb ; 
 int /*<<< orphan*/  gatt_cl_send_next_cmd_inq (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gatt_channel_congestion(tGATT_TCB *p_tcb, BOOLEAN congested)
{
    UINT8 i = 0;
    tGATT_REG *p_reg = NULL;
    UINT16 conn_id;
#if (GATTC_INCLUDED == TRUE)
    /* if uncongested, check to see if there is any more pending data */
    if (p_tcb != NULL && congested == FALSE) {
        gatt_cl_send_next_cmd_inq(p_tcb);
    }
#endif  ///GATTC_INCLUDED == TRUE
    /* notifying all applications for the connection up event */
    for (i = 0, p_reg = gatt_cb.cl_rcb ; i < GATT_MAX_APPS; i++, p_reg++) {
        if (p_reg->in_use) {
            if (p_reg->app_cb.p_congestion_cb) {
                conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_reg->gatt_if);
                (*p_reg->app_cb.p_congestion_cb)(conn_id, congested);
            }
        }
    }
}