#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * p_inst_id; int /*<<< orphan*/ * p_sub_code; } ;
struct TYPE_4__ {TYPE_1__ op_q; int /*<<< orphan*/ * p_adv_inst; } ;

/* Variables and functions */
 TYPE_2__ btm_multi_adv_cb ; 
 int /*<<< orphan*/ * btm_multi_adv_cb_ptr ; 
 int /*<<< orphan*/ * btm_multi_adv_idx_q_ptr ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void btm_ble_multi_adv_cleanup(void)
{
    if (btm_multi_adv_cb.p_adv_inst) {
        osi_free(btm_multi_adv_cb.p_adv_inst);
        btm_multi_adv_cb.p_adv_inst = NULL;
    }

    if (btm_multi_adv_cb.op_q.p_sub_code) {
        osi_free(btm_multi_adv_cb.op_q.p_sub_code);
        btm_multi_adv_cb.op_q.p_sub_code = NULL;
    }

    if (btm_multi_adv_cb.op_q.p_inst_id) {
        osi_free(btm_multi_adv_cb.op_q.p_inst_id);
        btm_multi_adv_cb.op_q.p_inst_id = NULL;
    }

#if BTM_DYNAMIC_MEMORY == TRUE
    osi_free(btm_multi_adv_cb_ptr);
    osi_free(btm_multi_adv_idx_q_ptr);
    btm_multi_adv_cb_ptr = NULL;
    btm_multi_adv_idx_q_ptr = NULL;
#endif
}