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
struct TYPE_4__ {scalar_t__* cback_cnt; } ;
struct TYPE_5__ {TYPE_1__ sr_cmd; } ;
typedef  TYPE_2__ tGATT_TCB ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t GATT_MAX_APPS ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN gatt_sr_is_cback_cnt_zero(tGATT_TCB *p_tcb )
{
    BOOLEAN status = TRUE;
#if (GATTS_INCLUDED == TRUE)
    UINT8   i;

    if (p_tcb) {
        for (i = 0; i < GATT_MAX_APPS; i ++) {
            if (p_tcb->sr_cmd.cback_cnt[i]) {
                status = FALSE;
                break;
            }
        }
    } else {
        status = FALSE;
    }
#endif  ///GATTS_INCLUDED == TRUE
    return status;
}