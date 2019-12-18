#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  transport; scalar_t__ remove_dev; } ;
struct TYPE_9__ {TYPE_4__ remove_acl; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;
typedef  TYPE_4__ tBTA_DM_API_REMOVE_ACL ;
typedef  size_t UINT8 ;
struct TYPE_8__ {size_t count; TYPE_1__* peer_device; } ;
struct TYPE_11__ {TYPE_2__ device_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  remove_dev_pending; int /*<<< orphan*/  peer_bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_GATTC_CancelOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTC_Refresh (int /*<<< orphan*/ ,int) ; 
 scalar_t__ BTM_IsAclConnectionUp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SecDeleteDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ bta_dm_cb ; 
 int /*<<< orphan*/  btm_remove_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_close_acl(tBTA_DM_MSG *p_data)
{
    tBTA_DM_API_REMOVE_ACL *p_remove_acl = &p_data->remove_acl;
    UINT8   index;

    APPL_TRACE_DEBUG("bta_dm_close_acl");

    if (BTM_IsAclConnectionUp(p_remove_acl->bd_addr, p_remove_acl->transport)) {
        for (index = 0; index < bta_dm_cb.device_list.count; index ++) {
            if (!bdcmp( bta_dm_cb.device_list.peer_device[index].peer_bdaddr, p_remove_acl->bd_addr)) {
                break;
            }
        }
        if (index != bta_dm_cb.device_list.count) {
            if (p_remove_acl->remove_dev) {
                bta_dm_cb.device_list.peer_device[index].remove_dev_pending = TRUE;
            }
        } else {
            APPL_TRACE_ERROR("unknown device, remove ACL failed");
        }
        /* Disconnect the ACL link */
        btm_remove_acl(p_remove_acl->bd_addr, p_remove_acl->transport);
    }
    /* if to remove the device from security database ? do it now */
    else if (p_remove_acl->remove_dev) {
        if (!BTM_SecDeleteDevice(p_remove_acl->bd_addr, p_remove_acl->transport)) {
            APPL_TRACE_ERROR("delete device from security database failed.");
        }
#if (BLE_INCLUDED == TRUE && GATTC_INCLUDED == TRUE)
        /* need to remove all pending background connection if any */
        BTA_GATTC_CancelOpen(0, p_remove_acl->bd_addr, FALSE);
        /* remove all cached GATT information */
        BTA_GATTC_Refresh(p_remove_acl->bd_addr, false);
#endif
    }
    /* otherwise, no action needed */

}