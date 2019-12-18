#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ att_lcid; int /*<<< orphan*/  transport; int /*<<< orphan*/  peer_bda; int /*<<< orphan*/  tcb_idx; } ;
typedef  TYPE_2__ tGATT_TCB ;
struct TYPE_8__ {int /*<<< orphan*/  (* p_conn_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  gatt_if; TYPE_1__ app_cb; scalar_t__ in_use; } ;
typedef  TYPE_3__ tGATT_REG ;
typedef  int /*<<< orphan*/  tGATT_BG_CONN_DEV ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_11__ {TYPE_3__* cl_rcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_CREATE_CONN_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_LINK_NO_IDLE_TIMEOUT ; 
 scalar_t__ GATT_MAX_APPS ; 
 int /*<<< orphan*/  GATT_SetIdleTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ L2CAP_ATT_CID ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_7__ gatt_cb ; 
 int /*<<< orphan*/ * gatt_find_bg_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_is_bg_dev_for_app (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_num_apps_hold_link (TYPE_2__*) ; 
 int /*<<< orphan*/  gatt_update_app_use_link_flag (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gatt_send_conn_cback(tGATT_TCB *p_tcb)
{
    UINT8               i;
    tGATT_REG           *p_reg;
    tGATT_BG_CONN_DEV   *p_bg_dev = NULL;
    UINT16              conn_id;

    p_bg_dev = gatt_find_bg_dev(p_tcb->peer_bda);

    /* notifying all applications for the connection up event */
    for (i = 0,  p_reg = gatt_cb.cl_rcb ; i < GATT_MAX_APPS; i++, p_reg++) {
        if (p_reg->in_use) {
            if (p_bg_dev && gatt_is_bg_dev_for_app(p_bg_dev, p_reg->gatt_if)) {
                gatt_update_app_use_link_flag(p_reg->gatt_if, p_tcb, TRUE, TRUE);
            }

            if (p_reg->app_cb.p_conn_cb) {
                conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_reg->gatt_if);
                (*p_reg->app_cb.p_conn_cb)(p_reg->gatt_if, p_tcb->peer_bda, conn_id,
                                           TRUE, 0, p_tcb->transport);
            }
        }
    }


    if (gatt_num_apps_hold_link(p_tcb) &&  p_tcb->att_lcid == L2CAP_ATT_CID ) {
        /* disable idle timeout if one or more clients are holding the link disable the idle timer */
        GATT_SetIdleTimeout(p_tcb->peer_bda, GATT_LINK_NO_IDLE_TIMEOUT, p_tcb->transport);
    }
}