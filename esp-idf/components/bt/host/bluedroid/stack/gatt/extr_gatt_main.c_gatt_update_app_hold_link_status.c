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
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 size_t GATT_MAX_APPS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,scalar_t__,size_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 scalar_t__ TRUE ; 

void gatt_update_app_hold_link_status (tGATT_IF gatt_if, tGATT_TCB *p_tcb, BOOLEAN is_add)
{
    UINT8 i;
    BOOLEAN found = FALSE;

    if (p_tcb == NULL) {
        GATT_TRACE_ERROR("gatt_update_app_hold_link_status p_tcb=NULL");
        return;
    }


    for (i = 0; i < GATT_MAX_APPS; i++) {
        if (p_tcb->app_hold_link[i] ==  gatt_if) {
            found = TRUE;
            if (!is_add) {
                p_tcb->app_hold_link[i] = 0;
                break;
            }
        }
    }

    if (!found && is_add) {
        for (i = 0; i < GATT_MAX_APPS; i++) {
            if (p_tcb->app_hold_link[i] ==  0) {
                p_tcb->app_hold_link[i] = gatt_if;
                found = TRUE;
                break;
            }
        }
    }

    GATT_TRACE_DEBUG("gatt_update_app_hold_link_status found=%d[1-found] idx=%d gatt_if=%d is_add=%d", found, i, gatt_if, is_add);

}