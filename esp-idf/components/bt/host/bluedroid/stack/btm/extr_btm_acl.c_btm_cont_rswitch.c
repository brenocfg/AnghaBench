#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sec_flags; int /*<<< orphan*/  rs_disc_pending; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
struct TYPE_7__ {scalar_t__ switch_role_state; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  link_role; int /*<<< orphan*/  encrypt_state; int /*<<< orphan*/  hci_handle; } ;
typedef  TYPE_2__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_IDLE ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_IN_PROGRESS ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_MODE_CHANGE ; 
 int /*<<< orphan*/  BTM_EPR_AVAILABLE (TYPE_2__*) ; 
 int BTM_SEC_ENCRYPTED ; 
 int /*<<< orphan*/  BTM_SEC_RS_PENDING ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_acl_report_role_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btsnd_hcic_set_conn_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_switch_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_cont_rswitch (tACL_CONN *p, tBTM_SEC_DEV_REC *p_dev_rec,
                       UINT8 hci_status)
{
    BOOLEAN sw_ok = TRUE;
    BTM_TRACE_DEBUG ("btm_cont_rswitch\n");
    /* Check to see if encryption needs to be turned off if pending
       change of link key or role switch */
    if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE) {
        /* Must turn off Encryption first if necessary */
        /* Some devices do not support switch or change of link key while encryption is on */
        if (p_dev_rec != NULL && ((p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED) != 0)
                && !BTM_EPR_AVAILABLE(p)) {
            if (btsnd_hcic_set_conn_encrypt (p->hci_handle, FALSE)) {
                p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF;
                if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE) {
                    p->switch_role_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF;
                }
            } else {
                /* Error occurred; set states back to Idle */
                if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE) {
                    sw_ok = FALSE;
                }
            }
        } else    /* Encryption not used or EPR supported, continue with switch
                   and/or change of link key */
        {
            if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE) {
                p->switch_role_state = BTM_ACL_SWKEY_STATE_IN_PROGRESS;
#if BTM_DISC_DURING_RS == TRUE
                if (p_dev_rec) {
                    p_dev_rec->rs_disc_pending = BTM_SEC_RS_PENDING;
                }
#endif
                sw_ok = btsnd_hcic_switch_role (p->remote_addr, (UINT8)!p->link_role);
            }
        }

        if (!sw_ok) {
            p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;
            btm_acl_report_role_change(hci_status, p->remote_addr);
        }
    }
}