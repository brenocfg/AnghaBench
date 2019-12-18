#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* cback_cnt; } ;
struct TYPE_6__ {TYPE_1__ sr_cmd; } ;
typedef  TYPE_2__ tGATT_TCB ;
typedef  scalar_t__ tGATT_IF ;
typedef  size_t UINT8 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  gatt_sr_reset_cback_cnt (TYPE_2__*) ; 

void gatt_sr_update_cback_cnt(tGATT_TCB *p_tcb, tGATT_IF gatt_if, BOOLEAN is_inc, BOOLEAN is_reset_first)
{
#if (GATTS_INCLUDED == TRUE)
    UINT8 idx = ((UINT8) gatt_if) - 1 ;

    if (p_tcb) {
        if (is_reset_first) {
            gatt_sr_reset_cback_cnt(p_tcb);
        }
        if (is_inc) {
            p_tcb->sr_cmd.cback_cnt[idx]++;
        } else {
            if ( p_tcb->sr_cmd.cback_cnt[idx]) {
                p_tcb->sr_cmd.cback_cnt[idx]--;
            }
        }
    }
#endif  ///GATTS_INCLUDED == TRUE
}