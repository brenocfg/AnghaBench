#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ link_state; scalar_t__ in_use; int /*<<< orphan*/  acl_priority; scalar_t__ link_role; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ UINT8 ;
struct TYPE_6__ {TYPE_1__* lcb_pool; } ;
typedef  scalar_t__ BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ HCI_SUCCESS ; 
 scalar_t__ LST_CONNECTING_WAIT_SWITCH ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ l2cb ; 
 int /*<<< orphan*/  l2cu_create_conn_after_switch (TYPE_1__*) ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_set_acl_priority (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2c_link_role_changed (BD_ADDR bd_addr, UINT8 new_role, UINT8 hci_status)
{
    tL2C_LCB *p_lcb;
    int      xx;

    /* Make sure not called from HCI Command Status (bd_addr and new_role are invalid) */
    if (bd_addr) {
        /* If here came form hci role change event */
        p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr, BT_TRANSPORT_BR_EDR);
        if (p_lcb) {
            p_lcb->link_role = new_role;

            /* Reset high priority link if needed */
            if (hci_status == HCI_SUCCESS) {
                l2cu_set_acl_priority(bd_addr, p_lcb->acl_priority, TRUE);
            }
        }
    }

    /* Check if any LCB was waiting for switch to be completed */
    for (xx = 0, p_lcb = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
        if ((p_lcb->in_use) && (p_lcb->link_state == LST_CONNECTING_WAIT_SWITCH)) {
            l2cu_create_conn_after_switch (p_lcb);
        }
    }
}