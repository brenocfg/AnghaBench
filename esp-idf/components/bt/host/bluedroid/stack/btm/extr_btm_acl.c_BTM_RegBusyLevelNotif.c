#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BL_EVENT_MASK ;
typedef  int /*<<< orphan*/  tBTM_BL_CHANGE_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/ * p_bl_changed_cb; int /*<<< orphan*/  bl_evt_mask; int /*<<< orphan*/  busy_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BUSY ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 TYPE_1__ btm_cb ; 

tBTM_STATUS BTM_RegBusyLevelNotif (tBTM_BL_CHANGE_CB *p_cb, UINT8 *p_level,
                                   tBTM_BL_EVENT_MASK evt_mask)
{
    BTM_TRACE_DEBUG ("BTM_RegBusyLevelNotif\n");
    if (p_level) {
        *p_level = btm_cb.busy_level;
    }

    btm_cb.bl_evt_mask = evt_mask;

    if (!p_cb) {
        btm_cb.p_bl_changed_cb = NULL;
    } else if (btm_cb.p_bl_changed_cb) {
        return (BTM_BUSY);
    } else {
        btm_cb.p_bl_changed_cb = p_cb;
    }

    return (BTM_SUCCESS);
}