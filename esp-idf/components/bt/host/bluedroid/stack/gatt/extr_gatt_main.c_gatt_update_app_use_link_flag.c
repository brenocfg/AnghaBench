#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ att_lcid; int /*<<< orphan*/  transport; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_IF ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_GetHCIConnHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_INVALID_ACL_HANDLE ; 
 int /*<<< orphan*/  GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP ; 
 int /*<<< orphan*/  GATT_LINK_NO_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  GATT_SetIdleTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,...) ; 
 scalar_t__ L2CAP_ATT_CID ; 
 int /*<<< orphan*/  gatt_num_apps_hold_link (TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_update_app_hold_link_status (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 

void gatt_update_app_use_link_flag (tGATT_IF gatt_if, tGATT_TCB *p_tcb, BOOLEAN is_add, BOOLEAN check_acl_link)
{
    GATT_TRACE_DEBUG("gatt_update_app_use_link_flag  is_add=%d chk_link=%d",
                     is_add, check_acl_link);

    gatt_update_app_hold_link_status(gatt_if, p_tcb, is_add);

    if (check_acl_link &&
            p_tcb &&
            p_tcb->att_lcid == L2CAP_ATT_CID && /* only update link idle timer for fixed channel */
            (BTM_GetHCIConnHandle(p_tcb->peer_bda, p_tcb->transport) != GATT_INVALID_ACL_HANDLE)) {
        if (is_add) {
            GATT_TRACE_DEBUG("GATT disables link idle timer");
            /* acl link is connected disable the idle timeout */
            GATT_SetIdleTimeout(p_tcb->peer_bda, GATT_LINK_NO_IDLE_TIMEOUT, p_tcb->transport);
        } else {
            if (!gatt_num_apps_hold_link(p_tcb)) {
                /* acl link is connected but no application needs to use the link
                   so set the timeout value to GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP seconds */
                GATT_TRACE_DEBUG("GATT starts link idle timer =%d sec", GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP);
                GATT_SetIdleTimeout(p_tcb->peer_bda, GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP, p_tcb->transport);
            }

        }
    }
}