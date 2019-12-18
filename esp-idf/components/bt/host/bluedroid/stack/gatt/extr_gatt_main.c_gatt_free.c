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
struct TYPE_6__ {int /*<<< orphan*/ * hdl_list; int /*<<< orphan*/  hdl_list_info; TYPE_2__* tcb; int /*<<< orphan*/ * pending_new_srv_start_q; int /*<<< orphan*/ * srv_chg_clt_q; int /*<<< orphan*/ * sign_op_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/ * multi_rsp_q; } ;
struct TYPE_5__ {TYPE_1__ sr_cmd; int /*<<< orphan*/  ind_ack_timer_ent; int /*<<< orphan*/  conf_timer_ent; int /*<<< orphan*/ * pending_ind_q; int /*<<< orphan*/ * pending_enc_clcb; } ;
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_RESET (int /*<<< orphan*/ ) ; 
 int GATT_MAX_PHY_CHANNEL ; 
 int GATT_MAX_SR_PROFILES ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  btu_free_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ gatt_cb ; 
 int /*<<< orphan*/  gatt_cb_ptr ; 
 int /*<<< orphan*/  gatt_free_attr_value_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_free_hdl_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_remove_an_item_from_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void gatt_free(void)
{
    int i;
    GATT_TRACE_DEBUG("gatt_free()");
    fixed_queue_free(gatt_cb.sign_op_queue, NULL);
    gatt_cb.sign_op_queue = NULL;
    fixed_queue_free(gatt_cb.srv_chg_clt_q, NULL);
    gatt_cb.srv_chg_clt_q = NULL;
    fixed_queue_free(gatt_cb.pending_new_srv_start_q, NULL);
    gatt_cb.pending_new_srv_start_q = NULL;

    for (i = 0; i < GATT_MAX_PHY_CHANNEL; i++)
    {
        fixed_queue_free(gatt_cb.tcb[i].pending_enc_clcb, NULL);
        gatt_cb.tcb[i].pending_enc_clcb = NULL;

        fixed_queue_free(gatt_cb.tcb[i].pending_ind_q, NULL);
        gatt_cb.tcb[i].pending_ind_q = NULL;

        btu_free_timer(&gatt_cb.tcb[i].conf_timer_ent);
        memset(&gatt_cb.tcb[i].conf_timer_ent, 0, sizeof(TIMER_LIST_ENT));

        btu_free_timer(&gatt_cb.tcb[i].ind_ack_timer_ent);
        memset(&gatt_cb.tcb[i].ind_ack_timer_ent, 0, sizeof(TIMER_LIST_ENT));

#if (GATTS_INCLUDED == TRUE)
        fixed_queue_free(gatt_cb.tcb[i].sr_cmd.multi_rsp_q, NULL);
        gatt_cb.tcb[i].sr_cmd.multi_rsp_q = NULL;
#endif /* #if (GATTS_INCLUDED == TRUE) */
    }

#if (GATTS_INCLUDED == TRUE)
    for (i = 0; i < GATT_MAX_SR_PROFILES; i++) {
        gatt_remove_an_item_from_list(&gatt_cb.hdl_list_info, &gatt_cb.hdl_list[i]);
        gatt_free_attr_value_buffer(&gatt_cb.hdl_list[i]);
        gatt_free_hdl_buffer(&gatt_cb.hdl_list[i]);
    }
#endif /* #if (GATTS_INCLUDED == TRUE) */
#if GATT_DYNAMIC_MEMORY
    FREE_AND_RESET(gatt_cb_ptr);
#endif /* #if GATT_DYNAMIC_MEMORY */
}