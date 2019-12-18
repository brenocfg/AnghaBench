#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_4__ {int /*<<< orphan*/  sec_flags; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
struct TYPE_5__ {scalar_t__ pairing_state; int /*<<< orphan*/  acl_disc_reason; int /*<<< orphan*/  pairing_bda; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_PAIR_STATE_WAIT_AUTH_COMPLETE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM ; 
 int /*<<< orphan*/  BTM_SEC_16_DIGIT_PIN_AUTHED ; 
 int /*<<< orphan*/  BTM_SEC_LINK_KEY_AUTHED ; 
 scalar_t__ BTM_SUCCESS ; 
 scalar_t__ BTM_SUCCESS_NO_SECURITY ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_SECURITY ; 
 int /*<<< orphan*/  HCI_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ btm_cb ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_pair_state_descr (scalar_t__) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_user_conf_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BTM_ConfirmReqReply(tBTM_STATUS res, BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
    BTM_TRACE_EVENT ("BTM_ConfirmReqReply() State: %s  Res: %u",
                     btm_pair_state_descr(btm_cb.pairing_state), res);
#endif  ///BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE
    /* If timeout already expired or has been canceled, ignore the reply */
    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM)
            ||  (memcmp (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN) != 0) ) {
        return;
    }

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);

    if ( (res == BTM_SUCCESS) || (res == BTM_SUCCESS_NO_SECURITY) ) {
        btm_cb.acl_disc_reason = HCI_SUCCESS;

        if (res == BTM_SUCCESS) {
            if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL) {
                p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_AUTHED;
            }
            p_dev_rec->sec_flags |= BTM_SEC_16_DIGIT_PIN_AUTHED;
        }

        btsnd_hcic_user_conf_reply (bd_addr, TRUE);
    } else {
        /* Report authentication failed event from state BTM_PAIR_STATE_WAIT_AUTH_COMPLETE */
        btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
        btsnd_hcic_user_conf_reply (bd_addr, FALSE);
    }
}