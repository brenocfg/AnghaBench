#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  event; } ;
struct TYPE_13__ {TYPE_2__ hdr; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
struct TYPE_14__ {scalar_t__ status; scalar_t__ auto_update; int /*<<< orphan*/  bda; int /*<<< orphan*/  bta_conn_id; TYPE_3__* p_q_cmd; TYPE_1__* p_srcb; int /*<<< orphan*/  disc_active; } ;
typedef  TYPE_4__ tBTA_GATTC_CLCB ;
struct TYPE_11__ {int /*<<< orphan*/  server_bda; TYPE_3__* p_srvc_list; int /*<<< orphan*/ * p_srvc_cache; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ BTA_GATTC_DISC_WAITING ; 
 int /*<<< orphan*/  BTA_GATTC_INT_DISCOVER_EVT ; 
 int /*<<< orphan*/  BTA_GATTC_SERV_IDLE ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  UNUSED (TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_cache_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_register_service_change_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_sm_execute (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (TYPE_3__*) ; 

void bta_gattc_disc_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_DATA *p_q_cmd = p_clcb->p_q_cmd;
    UNUSED(p_data);

    APPL_TRACE_DEBUG("bta_gattc_disc_cmpl conn_id=%d, status = %d", p_clcb->bta_conn_id, p_clcb->status);

    p_clcb->p_srcb->state = BTA_GATTC_SERV_IDLE;
    p_clcb->disc_active = FALSE;

    if (p_clcb->status != GATT_SUCCESS) {
        /* clean up cache */
        if (p_clcb->p_srcb && p_clcb->p_srcb->p_srvc_cache) {
            list_free(p_clcb->p_srcb->p_srvc_cache);
            p_clcb->p_srcb->p_srvc_cache = NULL;
        }
#if(GATTC_CACHE_NVS == TRUE)
        /* used to reset cache in application */
        bta_gattc_cache_reset(p_clcb->p_srcb->server_bda);
#endif
    }
    if (p_clcb->p_srcb && p_clcb->p_srcb->p_srvc_list) {
        /* release pending attribute list buffer */
        osi_free(p_clcb->p_srcb->p_srvc_list);
        p_clcb->p_srcb->p_srvc_list = NULL;
        //osi_free_and_reset((void **)&p_clcb->p_srcb->p_srvc_list);
    }

    if (p_clcb->auto_update == BTA_GATTC_DISC_WAITING) {
        /* start discovery again */
        bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_DISCOVER_EVT, NULL);
    }
    /* get any queued command to proceed */
    else if (p_q_cmd != NULL) {
        p_clcb->p_q_cmd = NULL;
        /* execute pending operation of link block still present */
        if (l2cu_find_lcb_by_bd_addr(p_clcb->p_srcb->server_bda, BT_TRANSPORT_LE) != NULL) {
            bta_gattc_sm_execute(p_clcb, p_q_cmd->hdr.event, p_q_cmd);
        }
        /* if the command executed requeued the cmd, we don't
         * want to free the underlying buffer that's being
         * referenced by p_clcb->p_q_cmd
         */
        if (p_q_cmd != p_clcb->p_q_cmd) {
            osi_free(p_q_cmd);
            p_q_cmd = NULL;
        }
    }

    //register service change
    bta_gattc_register_service_change_notify(p_clcb->bta_conn_id, p_clcb->bda);

}