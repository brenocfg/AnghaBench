#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ in_use; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  size_t UINT8 ;
struct TYPE_5__ {TYPE_1__* tcb; } ;

/* Variables and functions */
 size_t GATT_MAX_PHY_CHANNEL ; 
 TYPE_3__ gatt_cb ; 

tGATT_TCB *gatt_get_tcb_by_idx(UINT8 tcb_idx)
{
    tGATT_TCB   *p_tcb = NULL;

    if ( (tcb_idx < GATT_MAX_PHY_CHANNEL) && gatt_cb.tcb[tcb_idx].in_use) {
        p_tcb = &gatt_cb.tcb[tcb_idx];
    }

    return p_tcb;
}