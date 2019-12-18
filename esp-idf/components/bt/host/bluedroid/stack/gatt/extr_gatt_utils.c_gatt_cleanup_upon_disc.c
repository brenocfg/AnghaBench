#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * multi_rsp_q; } ;
struct TYPE_18__ {int /*<<< orphan*/  tcb_idx; TYPE_1__ sr_cmd; int /*<<< orphan*/  conf_timer_ent; int /*<<< orphan*/  ind_ack_timer_ent; } ;
typedef  TYPE_3__ tGATT_TCB ;
struct TYPE_17__ {int /*<<< orphan*/  (* p_conn_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  gatt_if; TYPE_2__ app_cb; scalar_t__ in_use; } ;
typedef  TYPE_4__ tGATT_REG ;
struct TYPE_20__ {scalar_t__ operation; int /*<<< orphan*/  clcb_idx; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  rsp_timer_ent; TYPE_3__* p_tcb; scalar_t__ in_use; } ;
typedef  TYPE_5__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_15__ {TYPE_4__* cl_rcb; TYPE_5__* clcb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_Recovery_Pre_State () ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATTC_OPTYPE_NONE ; 
 int /*<<< orphan*/  GATT_CH_CLOSE ; 
 size_t GATT_CL_MAX_LCB ; 
 int /*<<< orphan*/  GATT_CREATE_CONN_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_ERROR ; 
 size_t GATT_MAX_APPS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  btu_free_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_14__ gatt_cb ; 
 int /*<<< orphan*/  gatt_clcb_dealloc (TYPE_5__*) ; 
 int /*<<< orphan*/  gatt_delete_dev_from_srv_chg_clt_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_free_pending_enc_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  gatt_free_pending_ind (TYPE_3__*) ; 
 int /*<<< orphan*/  gatt_free_pending_prepare_write_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  gatt_set_ch_state (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osi_free_func ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gatt_cleanup_upon_disc(BD_ADDR bda, UINT16 reason, tBT_TRANSPORT transport)
{
    tGATT_TCB       *p_tcb = NULL;
    tGATT_CLCB      *p_clcb;
    UINT8           i;
    UINT16          conn_id;
    tGATT_REG        *p_reg = NULL;


    GATT_TRACE_DEBUG ("gatt_cleanup_upon_disc ");

    if ((p_tcb = gatt_find_tcb_by_addr(bda, transport)) != NULL) {
        GATT_TRACE_DEBUG ("found p_tcb ");
        gatt_set_ch_state(p_tcb, GATT_CH_CLOSE);
        for (i = 0; i < GATT_CL_MAX_LCB; i ++) {
            p_clcb = &gatt_cb.clcb[i];
            if (p_clcb->in_use && p_clcb->p_tcb == p_tcb) {
                btu_stop_timer(&p_clcb->rsp_timer_ent);
                GATT_TRACE_DEBUG ("found p_clcb conn_id=%d clcb_idx=%d", p_clcb->conn_id, p_clcb->clcb_idx);
                if (p_clcb->operation != GATTC_OPTYPE_NONE) {
                    gatt_end_operation(p_clcb, GATT_ERROR, NULL);
                }

                gatt_clcb_dealloc(p_clcb);

            }
        }

        btu_free_timer (&p_tcb->ind_ack_timer_ent);
        btu_free_timer (&p_tcb->conf_timer_ent);
        gatt_free_pending_ind(p_tcb);
        gatt_free_pending_enc_queue(p_tcb);
        gatt_free_pending_prepare_write_queue(p_tcb);
#if (GATTS_INCLUDED)
        fixed_queue_free(p_tcb->sr_cmd.multi_rsp_q, osi_free_func);
        p_tcb->sr_cmd.multi_rsp_q = NULL;
#endif /* #if (GATTS_INCLUDED) */
        for (i = 0; i < GATT_MAX_APPS; i ++) {
            p_reg = &gatt_cb.cl_rcb[i];
            if (p_reg->in_use && p_reg->app_cb.p_conn_cb) {
                conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_reg->gatt_if);
                GATT_TRACE_DEBUG ("found p_reg tcb_idx=%d gatt_if=%d  conn_id=0x%x", p_tcb->tcb_idx, p_reg->gatt_if, conn_id);
                (*p_reg->app_cb.p_conn_cb)(p_reg->gatt_if,  bda, conn_id, FALSE, reason, transport);
            }
        }
        memset(p_tcb, 0, sizeof(tGATT_TCB));

    } else {
        GATT_TRACE_DEBUG ("exit gatt_cleanup_upon_disc ");
        BTM_Recovery_Pre_State();
    }
    gatt_delete_dev_from_srv_chg_clt_list(bda);
}