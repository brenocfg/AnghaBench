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
struct TYPE_3__ {void* busy_level; int /*<<< orphan*/  event; int /*<<< orphan*/  busy_level_flags; } ;
typedef  TYPE_1__ tBTM_BL_UPDATE_DATA ;
typedef  int /*<<< orphan*/  tBTM_BL_EVENT_DATA ;
typedef  int tBTM_BLI_EVENT ;
typedef  void* UINT8 ;
struct TYPE_4__ {scalar_t__ is_inquiry; void* busy_level; int bl_evt_mask; int /*<<< orphan*/  (* p_bl_changed_cb ) (int /*<<< orphan*/ *) ;void* is_paging; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
#define  BTM_BLI_ACL_DOWN_EVT 134 
#define  BTM_BLI_ACL_UP_EVT 133 
#define  BTM_BLI_INQ_CANCEL_EVT 132 
#define  BTM_BLI_INQ_DONE_EVT 131 
#define  BTM_BLI_INQ_EVT 130 
#define  BTM_BLI_PAGE_DONE_EVT 129 
#define  BTM_BLI_PAGE_EVT 128 
 int /*<<< orphan*/  BTM_BL_INQUIRY_CANCELLED ; 
 int /*<<< orphan*/  BTM_BL_INQUIRY_COMPLETE ; 
 int /*<<< orphan*/  BTM_BL_INQUIRY_STARTED ; 
 int /*<<< orphan*/  BTM_BL_PAGING_COMPLETE ; 
 int /*<<< orphan*/  BTM_BL_PAGING_STARTED ; 
 int /*<<< orphan*/  BTM_BL_UPDATE_EVT ; 
 int BTM_BL_UPDATE_MASK ; 
 void* BTM_GetNumAclLinks () ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 void* FALSE ; 
 void* TRUE ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void btm_acl_update_busy_level (tBTM_BLI_EVENT event)
{
    tBTM_BL_UPDATE_DATA  evt;
    UINT8 busy_level;
    BTM_TRACE_DEBUG ("btm_acl_update_busy_level\n");
    BOOLEAN old_inquiry_state = btm_cb.is_inquiry;
    switch (event) {
    case BTM_BLI_ACL_UP_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_ACL_UP_EVT\n");
        break;
    case BTM_BLI_ACL_DOWN_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_ACL_DOWN_EVT\n");
        break;
    case BTM_BLI_PAGE_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_PAGE_EVT\n");
        btm_cb.is_paging = TRUE;
        evt.busy_level_flags = BTM_BL_PAGING_STARTED;
        break;
    case BTM_BLI_PAGE_DONE_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_PAGE_DONE_EVT\n");
        btm_cb.is_paging = FALSE;
        evt.busy_level_flags = BTM_BL_PAGING_COMPLETE;
        break;
    case BTM_BLI_INQ_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_INQ_EVT\n");
        btm_cb.is_inquiry = TRUE;
        evt.busy_level_flags = BTM_BL_INQUIRY_STARTED;
        break;
    case BTM_BLI_INQ_CANCEL_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_INQ_CANCEL_EVT\n");
        btm_cb.is_inquiry = FALSE;
        evt.busy_level_flags = BTM_BL_INQUIRY_CANCELLED;
        break;
    case BTM_BLI_INQ_DONE_EVT:
        BTM_TRACE_DEBUG ("BTM_BLI_INQ_DONE_EVT\n");
        btm_cb.is_inquiry = FALSE;
        evt.busy_level_flags = BTM_BL_INQUIRY_COMPLETE;
        break;
    }

    if (btm_cb.is_paging || btm_cb.is_inquiry) {
        busy_level = 10;
    } else {
        busy_level = BTM_GetNumAclLinks();
    }

    if ((busy_level != btm_cb.busy_level) || (old_inquiry_state != btm_cb.is_inquiry)) {
        evt.event         = BTM_BL_UPDATE_EVT;
        evt.busy_level    = busy_level;
        btm_cb.busy_level = busy_level;
        if (btm_cb.p_bl_changed_cb && (btm_cb.bl_evt_mask & BTM_BL_UPDATE_MASK)) {
            (*btm_cb.p_bl_changed_cb)((tBTM_BL_EVENT_DATA *)&evt);
        }
    }
}