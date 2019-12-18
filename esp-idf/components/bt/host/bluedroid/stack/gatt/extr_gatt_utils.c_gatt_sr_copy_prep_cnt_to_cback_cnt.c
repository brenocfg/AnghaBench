#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* cback_cnt; } ;
struct TYPE_5__ {TYPE_1__ sr_cmd; scalar_t__* prep_cnt; } ;
typedef  TYPE_2__ tGATT_TCB ;
typedef  size_t UINT8 ;

/* Variables and functions */
 size_t GATT_MAX_APPS ; 

void gatt_sr_copy_prep_cnt_to_cback_cnt(tGATT_TCB *p_tcb )
{
#if (GATTS_INCLUDED == TRUE)
    UINT8 i;

    if (p_tcb) {
        for (i = 0; i < GATT_MAX_APPS; i ++) {
            if (p_tcb->prep_cnt[i]) {
                p_tcb->sr_cmd.cback_cnt[i] = 1;
            }
        }
    }
#endif  ///GATTS_INCLUDED == TRUE
}