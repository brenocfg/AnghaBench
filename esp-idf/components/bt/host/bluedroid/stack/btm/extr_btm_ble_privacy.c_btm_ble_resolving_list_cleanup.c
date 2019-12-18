#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * resolve_q_action; int /*<<< orphan*/ * resolve_q_random_pseudo; } ;
typedef  TYPE_2__ tBTM_BLE_RESOLVE_Q ;
struct TYPE_5__ {int /*<<< orphan*/ * irk_list_mask; TYPE_2__ resolving_list_pend_q; } ;
struct TYPE_8__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_ble_resolving_list_max_size ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_4__ btm_cb ; 
 TYPE_3__* controller_get_interface () ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void btm_ble_resolving_list_cleanup(void)
{
    tBTM_BLE_RESOLVE_Q *p_q = &btm_cb.ble_ctr_cb.resolving_list_pend_q;

    if (p_q->resolve_q_random_pseudo) {
        osi_free(p_q->resolve_q_random_pseudo);
        p_q->resolve_q_random_pseudo = NULL;
    }

    if (p_q->resolve_q_action) {
        osi_free(p_q->resolve_q_action);
        p_q->resolve_q_action = NULL;
    }

    controller_get_interface()->set_ble_resolving_list_max_size(0);
    if (btm_cb.ble_ctr_cb.irk_list_mask) {
        osi_free(btm_cb.ble_ctr_cb.irk_list_mask);
        btm_cb.ble_ctr_cb.irk_list_mask = NULL;
    }

}