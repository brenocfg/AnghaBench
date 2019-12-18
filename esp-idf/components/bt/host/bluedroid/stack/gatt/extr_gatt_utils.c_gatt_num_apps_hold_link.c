#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* app_hold_link; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  size_t UINT8 ;

/* Variables and functions */
 size_t GATT_MAX_APPS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,size_t) ; 

UINT8 gatt_num_apps_hold_link(tGATT_TCB *p_tcb)
{
    UINT8 i, num = 0;

    for (i = 0; i < GATT_MAX_APPS; i ++) {
        if (p_tcb->app_hold_link[i]) {
            num ++;
        }
    }

    GATT_TRACE_DEBUG("gatt_num_apps_hold_link   num=%d",  num);
    return num;
}