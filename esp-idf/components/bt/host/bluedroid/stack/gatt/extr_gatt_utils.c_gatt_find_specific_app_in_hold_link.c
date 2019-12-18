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
typedef  scalar_t__ tGATT_IF ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t GATT_MAX_APPS ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN gatt_find_specific_app_in_hold_link(tGATT_TCB *p_tcb, tGATT_IF p_gatt_if)
{
    UINT8 i;
    BOOLEAN found = FALSE;

    for (i = 0; i < GATT_MAX_APPS; i ++) {
        if (p_tcb->app_hold_link[i] && p_tcb->app_hold_link[i] == p_gatt_if) {
            found = TRUE;
            break;
        }
    }
    return found;
}