#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* prep_cnt; int /*<<< orphan*/  tcb_idx; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  scalar_t__ tGATT_IF ;
typedef  size_t UINT8 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gatt_sr_reset_prep_cnt (TYPE_1__*) ; 

void gatt_sr_update_prep_cnt(tGATT_TCB *p_tcb, tGATT_IF gatt_if, BOOLEAN is_inc, BOOLEAN is_reset_first)
{
    UINT8 idx = ((UINT8) gatt_if) - 1 ;

    GATT_TRACE_DEBUG("gatt_sr_update_prep_cnt tcb idx=%d gatt_if=%d is_inc=%d is_reset_first=%d",
                     p_tcb->tcb_idx, gatt_if, is_inc, is_reset_first);

    if (p_tcb) {
        if (is_reset_first) {
            gatt_sr_reset_prep_cnt(p_tcb);
        }
        if (is_inc) {
            p_tcb->prep_cnt[idx]++;
        } else {
            if (p_tcb->prep_cnt[idx]) {
                p_tcb->prep_cnt[idx]--;
            }
        }
    }
}