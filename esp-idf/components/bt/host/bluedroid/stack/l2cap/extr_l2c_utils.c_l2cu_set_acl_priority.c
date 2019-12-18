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
struct TYPE_3__ {scalar_t__ acl_priority; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_IS_BRCM_CONTROLLER () ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 scalar_t__ HCI_BRCM_ACL_PRIORITY_HIGH ; 
 scalar_t__ HCI_BRCM_ACL_PRIORITY_LOW ; 
 int HCI_BRCM_ACL_PRIORITY_PARAM_SIZE ; 
 int /*<<< orphan*/  HCI_BRCM_SET_ACL_PRIORITY ; 
 scalar_t__ L2CAP_PRIORITY_HIGH ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  l2c_link_adjust_allocation () ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN l2cu_set_acl_priority (BD_ADDR bd_addr, UINT8 priority, BOOLEAN reset_after_rs)
{
    tL2C_LCB            *p_lcb;
    UINT8               *pp;
    UINT8                command[HCI_BRCM_ACL_PRIORITY_PARAM_SIZE];
    UINT8                vs_param;

    //APPL_TRACE_EVENT("SET ACL PRIORITY %d", priority);

    /* Find the link control block for the acl channel */
    if ((p_lcb = l2cu_find_lcb_by_bd_addr(bd_addr, BT_TRANSPORT_BR_EDR)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no LCB for L2CA_SetAclPriority");
        return (FALSE);
    }

    if (BTM_IS_BRCM_CONTROLLER()) {
        /* Called from above L2CAP through API; send VSC if changed */
        if ((!reset_after_rs && (priority != p_lcb->acl_priority)) ||
                /* Called because of a master/slave role switch; if high resend VSC */
                ( reset_after_rs && p_lcb->acl_priority == L2CAP_PRIORITY_HIGH)) {
            pp = command;

            vs_param = (priority == L2CAP_PRIORITY_HIGH) ? HCI_BRCM_ACL_PRIORITY_HIGH : HCI_BRCM_ACL_PRIORITY_LOW;

            UINT16_TO_STREAM (pp, p_lcb->handle);
            UINT8_TO_STREAM  (pp, vs_param);

            BTM_VendorSpecificCommand (HCI_BRCM_SET_ACL_PRIORITY, HCI_BRCM_ACL_PRIORITY_PARAM_SIZE, command, NULL);

            /* Adjust lmp buffer allocation for this channel if priority changed */
            if (p_lcb->acl_priority != priority) {
                p_lcb->acl_priority = priority;
                l2c_link_adjust_allocation();
            }
        }
    }
    return (TRUE);
}