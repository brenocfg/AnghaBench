#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_2__ tGATT_TCB ;
struct TYPE_12__ {int /*<<< orphan*/  srv_chg; } ;
typedef  TYPE_3__ tGATTS_SRV_CHG_REQ ;
struct TYPE_13__ {int /*<<< orphan*/  srv_changed; } ;
typedef  TYPE_4__ tGATTS_SRV_CHG ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_srv_chg_callback ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_1__ cb_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATTS_SRV_CHG_CMD_UPDATE_CLIENT ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 TYPE_9__ gatt_cb ; 
 TYPE_4__* gatt_is_bda_in_the_srv_chg_clt_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gatts_proc_srv_chg_ind_ack(tGATT_TCB *p_tcb )
{
    tGATTS_SRV_CHG_REQ  req;
    tGATTS_SRV_CHG      *p_buf = NULL;

    GATT_TRACE_DEBUG("gatts_proc_srv_chg_ind_ack");

    if ((p_buf = gatt_is_bda_in_the_srv_chg_clt_list(p_tcb->peer_bda)) != NULL) {
        GATT_TRACE_DEBUG("NV update set srv chg = FALSE");
        p_buf->srv_changed = FALSE;
        memcpy(&req.srv_chg, p_buf, sizeof(tGATTS_SRV_CHG));
        if (gatt_cb.cb_info.p_srv_chg_callback) {
            (*gatt_cb.cb_info.p_srv_chg_callback)(GATTS_SRV_CHG_CMD_UPDATE_CLIENT, &req, NULL);
        }
    }
}