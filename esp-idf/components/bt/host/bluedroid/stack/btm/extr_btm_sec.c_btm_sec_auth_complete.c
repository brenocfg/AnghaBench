#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ sec_state; int* bd_addr; int sm4; int sec_flags; int pin_code_length; scalar_t__ link_key_type; int /*<<< orphan*/  hci_handle; scalar_t__ new_encryption_key_is_p256; int /*<<< orphan*/  security_required; int /*<<< orphan*/  sec_bd_name; int /*<<< orphan*/  dev_class; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ tBTM_PAIRING_STATE ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_auth_complete_callback ) (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_12__ {scalar_t__ pairing_state; int pairing_flags; TYPE_1__ api; int /*<<< orphan*/  pairing_bda; scalar_t__ collision_start_time; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_CMD_STARTED ; 
 int BTM_ERR_PROCESSING ; 
 scalar_t__ BTM_LKEY_TYPE_AUTH_COMB ; 
 scalar_t__ BTM_LKEY_TYPE_AUTH_COMB_P_256 ; 
 int BTM_PAIR_FLAGS_DISC_WHEN_DONE ; 
 int BTM_PAIR_FLAGS_WE_STARTED_DD ; 
 scalar_t__ BTM_PAIR_STATE_IDLE ; 
 int BTM_SEC_16_DIGIT_PIN_AUTHED ; 
 int BTM_SEC_AUTHENTICATED ; 
 int BTM_SEC_ENCRYPTED ; 
 scalar_t__ BTM_SEC_IS_SM4 (int) ; 
 int BTM_SEC_LE_LINK_KEY_AUTHED ; 
 int BTM_SEC_LE_LINK_KEY_KNOWN ; 
 int BTM_SEC_LINK_KEY_AUTHED ; 
 int BTM_SEC_LINK_KEY_KNOWN ; 
 int /*<<< orphan*/  BTM_SEC_OUT_AUTHENTICATE ; 
 scalar_t__ BTM_SEC_STATE_AUTHENTICATING ; 
 scalar_t__ BTM_SEC_STATE_IDLE ; 
 int BTM_SM4_RETRY ; 
 int /*<<< orphan*/  BTM_SetEncryption (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 int HCI_ERR_AUTH_FAILURE ; 
 int HCI_ERR_COMMAND_DISALLOWED ; 
 int HCI_ERR_CONN_CAUSE_LOCAL_HOST ; 
 int HCI_ERR_DIFF_TRANSACTION_COLLISION ; 
 int HCI_ERR_KEY_MISSING ; 
 int HCI_ERR_LMP_ERR_TRANS_COLLISION ; 
 int HCI_ERR_PEER_USER ; 
 int HCI_SUCCESS ; 
 scalar_t__ TRUE ; 
 TYPE_9__ btm_cb ; 
 TYPE_2__* btm_find_dev_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_pair_state_descr (scalar_t__) ; 
 int /*<<< orphan*/  btm_restore_mode () ; 
 int /*<<< orphan*/  btm_sec_auth_collision (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (scalar_t__) ; 
 int /*<<< orphan*/  btm_sec_dev_rec_cback_event (TYPE_2__*,int,scalar_t__) ; 
 int btm_sec_execute_procedure (TYPE_2__*) ; 
 scalar_t__ btm_sec_is_master (TYPE_2__*) ; 
 int /*<<< orphan*/  btm_sec_send_hci_disconnect (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ btm_sec_use_smp_br_chnl (TYPE_2__*) ; 
 int /*<<< orphan*/  l2cu_start_post_bond_timer (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void btm_sec_auth_complete (UINT16 handle, UINT8 status)
{
    UINT8            old_sm4;
    tBTM_PAIRING_STATE  old_state   = btm_cb.pairing_state;
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    BOOLEAN             are_bonding = FALSE;

    /* Commenting out trace due to obf/compilation problems.
    */
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
    if (p_dev_rec) {
        BTM_TRACE_EVENT ("Security Manager: auth_complete PairState: %s  handle:%u  status:%d  dev->sec_state: %u  Bda:%08x, RName:%s\n",
                         btm_pair_state_descr (btm_cb.pairing_state),
                         handle, status,
                         p_dev_rec->sec_state,
                         (p_dev_rec->bd_addr[2] << 24) + (p_dev_rec->bd_addr[3] << 16) + (p_dev_rec->bd_addr[4] << 8) + p_dev_rec->bd_addr[5],
                         p_dev_rec->sec_bd_name);
    } else {
        BTM_TRACE_EVENT ("Security Manager: auth_complete PairState: %s  handle:%u  status:%d\n",
                         btm_pair_state_descr (btm_cb.pairing_state),
                         handle, status);
    }
#endif

    /* For transaction collision we need to wait and repeat.  There is no need */
    /* for random timeout because only slave should receive the result */
    if ((status == HCI_ERR_LMP_ERR_TRANS_COLLISION) || (status == HCI_ERR_DIFF_TRANSACTION_COLLISION)) {
        btm_sec_auth_collision(handle);
        return;
    }
    btm_cb.collision_start_time = 0;

    btm_restore_mode();

    /* Check if connection was made just to do bonding.  If we authenticate
       the connection that is up, this is the last event received.
    */
    if (p_dev_rec
            && (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            && !(btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE)) {
        p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;

        l2cu_start_post_bond_timer (p_dev_rec->hci_handle);
    }

    if (!p_dev_rec) {
        return;
    }

    /* keep the old sm4 flag and clear the retry bit in control block */
    old_sm4 = p_dev_rec->sm4;
    p_dev_rec->sm4 &= ~BTM_SM4_RETRY;

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
            &&  (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            &&  (memcmp (p_dev_rec->bd_addr, btm_cb.pairing_bda, BD_ADDR_LEN) == 0) ) {
        are_bonding = TRUE;
    }

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
            &&  (memcmp (p_dev_rec->bd_addr, btm_cb.pairing_bda, BD_ADDR_LEN) == 0) ) {
        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
    }

    if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING) {
        if ( (btm_cb.api.p_auth_complete_callback && status != HCI_SUCCESS)
                &&  (old_state != BTM_PAIR_STATE_IDLE) ) {
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                    p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, status);
        }
        return;
    }

    /* There can be a race condition, when we are starting authentication and
    ** the peer device is doing encryption.
    ** If first we receive encryption change up, then initiated authentication
    ** can not be performed.  According to the spec we can not do authentication
    ** on the encrypted link, so device is correct.
    */
    if ((status == HCI_ERR_COMMAND_DISALLOWED)
            && ((p_dev_rec->sec_flags & (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED)) ==
                (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED))) {
        status = HCI_SUCCESS;
    }
    /* Currently we do not notify user if it is a keyboard which connects */
    /* User probably Disabled the keyboard while it was asleap.  Let her try */
    if (btm_cb.api.p_auth_complete_callback) {
        /* report the suthentication status */
        if (old_state != BTM_PAIR_STATE_IDLE) {
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                    p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, status);
        }
    }

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    /* If this is a bonding procedure can disconnect the link now */
    if (are_bonding) {
        p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;

        if (status != HCI_SUCCESS) {
            if (((status != HCI_ERR_PEER_USER) && (status != HCI_ERR_CONN_CAUSE_LOCAL_HOST))) {
                btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_PEER_USER, p_dev_rec->hci_handle);
            }
        } else {
            BTM_TRACE_DEBUG ("TRYING TO DECIDE IF CAN USE SMP_BR_CHNL\n");
            if (p_dev_rec->new_encryption_key_is_p256 && (btm_sec_use_smp_br_chnl(p_dev_rec))
                    /* no LE keys are available, do deriving */
                    && (!(p_dev_rec->sec_flags & BTM_SEC_LE_LINK_KEY_KNOWN) ||
                        /* or BR key is higher security than existing LE keys */
                        (!(p_dev_rec->sec_flags & BTM_SEC_LE_LINK_KEY_AUTHED) &&
                         (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_AUTHED)))) {
                BTM_TRACE_DEBUG ("link encrypted afer dedic bonding can use SMP_BR_CHNL\n");

                if (btm_sec_is_master(p_dev_rec)) {
                    // Encryption is required to start SM over BR/EDR
                    // indicate that this is encryption after authentication
                    BTM_SetEncryption(p_dev_rec->bd_addr, BT_TRANSPORT_BR_EDR, NULL, NULL);
                }
            }
            l2cu_start_post_bond_timer (p_dev_rec->hci_handle);
        }

        return;
    }

    /* If authentication failed, notify the waiting layer */
    if (status != HCI_SUCCESS) {
        if ((old_sm4 & BTM_SM4_RETRY) == 0) {
            /* allow retry only once */
            if (status == HCI_ERR_LMP_ERR_TRANS_COLLISION) {
                /* not retried yet. set the retry bit */
                p_dev_rec->sm4 |= BTM_SM4_RETRY;
                BTM_TRACE_DEBUG ("Collision retry sm4:x%x sec_flags:0x%x\n", p_dev_rec->sm4, p_dev_rec->sec_flags);
            }
            /* this retry for missing key is for Lisbon or later only.
             * Legacy device do not need this. the controller will drive the retry automatically */
            else if (HCI_ERR_KEY_MISSING == status && BTM_SEC_IS_SM4(p_dev_rec->sm4)) {
                /* not retried yet. set the retry bit */
                p_dev_rec->sm4 |= BTM_SM4_RETRY;
                p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_KNOWN;
                BTM_TRACE_DEBUG ("Retry for missing key sm4:x%x sec_flags:0x%x\n", p_dev_rec->sm4, p_dev_rec->sec_flags);

                /* With BRCM controller, we do not need to delete the stored link key in controller.
                If the stack may sit on top of other controller, we may need this
                BTM_DeleteStoredLinkKey (bd_addr, NULL); */
            }

            if (p_dev_rec->sm4 & BTM_SM4_RETRY) {
                btm_sec_execute_procedure (p_dev_rec);
                return;
            }
        }

        btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING, FALSE);

        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE) {
            btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE, p_dev_rec->hci_handle);
        }
        return;
    }

    p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;

    if (p_dev_rec->pin_code_length >= 16 ||
            p_dev_rec->link_key_type == BTM_LKEY_TYPE_AUTH_COMB ||
            p_dev_rec->link_key_type == BTM_LKEY_TYPE_AUTH_COMB_P_256) {
        // If we have MITM protection we have a higher level of security than
        // provided by 16 digits PIN
        p_dev_rec->sec_flags |= BTM_SEC_16_DIGIT_PIN_AUTHED;
    }

    /* Authentication succeeded, execute the next security procedure, if any */
    status = btm_sec_execute_procedure (p_dev_rec);

    /* If there is no next procedure, or procedure failed to start, notify the caller */
    if (status != BTM_CMD_STARTED) {
        btm_sec_dev_rec_cback_event (p_dev_rec, status, FALSE);
    }
}