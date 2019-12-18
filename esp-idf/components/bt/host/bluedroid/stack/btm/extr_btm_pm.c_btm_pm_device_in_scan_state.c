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
struct TYPE_3__ {int inq_active; } ;
struct TYPE_4__ {scalar_t__ busy_level; TYPE_1__ btm_inq_vars; int /*<<< orphan*/  page_queue; scalar_t__ is_paging; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BTM_BLE_INQ_ACTIVE_MASK ; 
 scalar_t__ BTM_BL_PAGING_STARTED ; 
 int BTM_BR_INQ_ACTIVE_MASK ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ ) ; 

BOOLEAN btm_pm_device_in_scan_state(void)
{
    /* Scan state-paging, inquiry, and trying to connect */

    /* Check for paging */
    if (btm_cb.is_paging || (!fixed_queue_is_empty(btm_cb.page_queue)) ||
            BTM_BL_PAGING_STARTED == btm_cb.busy_level) {
        BTM_TRACE_DEBUG("btm_pm_device_in_scan_state- paging");
        return TRUE;
    }

    /* Check for inquiry */
    if ((btm_cb.btm_inq_vars.inq_active & (BTM_BR_INQ_ACTIVE_MASK | BTM_BLE_INQ_ACTIVE_MASK)) != 0) {
        BTM_TRACE_DEBUG("btm_pm_device_in_scan_state- Inq active");
        return TRUE;
    }

    return FALSE;
}