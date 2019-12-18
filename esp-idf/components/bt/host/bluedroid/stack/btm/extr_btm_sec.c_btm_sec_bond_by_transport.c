#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBT_TRANSPORT ;
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_13__ {int sec_flags; scalar_t__ hci_handle; scalar_t__ ble_hci_handle; int* dev_class; int sm4; int /*<<< orphan*/  sec_state; scalar_t__** features; int /*<<< orphan*/  trusted_mask; void* is_originator; int /*<<< orphan*/  security_required; scalar_t__ pin_code_length; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
struct TYPE_14__ {scalar_t__ hci_handle; } ;
typedef  TYPE_3__ tACL_CONN ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_12__ {scalar_t__ pin_type; } ;
struct TYPE_16__ {scalar_t__ pairing_state; int /*<<< orphan*/  security_mode; void* pin_type_changed; TYPE_1__ cfg; int /*<<< orphan*/  pairing_flags; int /*<<< orphan*/  pairing_bda; int /*<<< orphan*/  pin_code; scalar_t__ pin_code_len; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* supports_simple_pairing ) () ;} ;
typedef  scalar_t__* BD_ADDR ;

/* Variables and functions */
 scalar_t__ BD_ADDR_LEN ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int BTM_COD_MAJOR_CLASS_MASK ; 
 int BTM_COD_MAJOR_PERIPHERAL ; 
 int BTM_COD_MINOR_KEYBOARD ; 
 scalar_t__ BTM_DeleteStoredLinkKey (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_PAIR_FLAGS_LE_ACTIVE ; 
 int /*<<< orphan*/  BTM_PAIR_FLAGS_WE_STARTED_DD ; 
 scalar_t__ BTM_PAIR_STATE_GET_REM_NAME ; 
 scalar_t__ BTM_PAIR_STATE_IDLE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_AUTH_COMPLETE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_PIN_REQ ; 
 int /*<<< orphan*/  BTM_ReadRemoteDeviceName (scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int BTM_SEC_AUTHENTICATED ; 
 int /*<<< orphan*/  BTM_SEC_COPY_TRUSTED_DEVICE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int BTM_SEC_ENCRYPTED ; 
 scalar_t__ BTM_SEC_INVALID_HANDLE ; 
 scalar_t__ BTM_SEC_IS_SM4_UNKNOWN (int) ; 
 int BTM_SEC_LE_AUTHENTICATED ; 
 int BTM_SEC_LE_MASK ; 
 int BTM_SEC_LINK_KEY_AUTHED ; 
 int BTM_SEC_LINK_KEY_KNOWN ; 
 int /*<<< orphan*/  BTM_SEC_MODE_SC ; 
 int /*<<< orphan*/  BTM_SEC_MODE_SP ; 
 int /*<<< orphan*/  BTM_SEC_MODE_SP_DEBUG ; 
 int BTM_SEC_NAME_KNOWN ; 
 int /*<<< orphan*/  BTM_SEC_OUT_AUTHENTICATE ; 
 int BTM_SEC_ROLE_SWITCHED ; 
 int /*<<< orphan*/  BTM_SEC_STATE_AUTHENTICATING ; 
 int BTM_SM4_CONN_PEND ; 
 int BTM_SM4_KNOWN ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*) ; 
 scalar_t__ BTM_WRONG_MODE ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 scalar_t__ HCI_EXT_FEATURES_PAGE_MAX ; 
 scalar_t__ HCI_PIN_TYPE_FIXED ; 
 scalar_t__ PIN_CODE_LEN ; 
 scalar_t__ SMP_Pair (scalar_t__*) ; 
 scalar_t__ SMP_STARTED ; 
 void* TRUE ; 
 TYPE_3__* btm_bda_to_acl (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  btm_ble_init_pseudo_addr (TYPE_2__*,scalar_t__*) ; 
 TYPE_9__ btm_cb ; 
 TYPE_2__* btm_find_or_alloc_dev (scalar_t__*) ; 
 int /*<<< orphan*/  btm_pair_state_descr (scalar_t__) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (scalar_t__) ; 
 scalar_t__ btm_sec_check_prefetch_pin (TYPE_2__*) ; 
 scalar_t__ btm_sec_dd_create_conn (TYPE_2__*) ; 
 int /*<<< orphan*/  btm_sec_start_authentication (TYPE_2__*) ; 
 int /*<<< orphan*/  btsnd_hcic_write_pin_type (scalar_t__) ; 
 TYPE_4__* controller_get_interface () ; 
 int /*<<< orphan*/  l2cu_update_lcb_4_bonding (scalar_t__*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

tBTM_STATUS btm_sec_bond_by_transport (BD_ADDR bd_addr, tBT_TRANSPORT transport,
                                       UINT8 pin_len, UINT8 *p_pin, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_STATUS      status;
#if (!CONFIG_BT_STACK_NO_LOG)
    UINT8            *p_features;
#endif
    UINT8            ii;
    tACL_CONN        *p = btm_bda_to_acl(bd_addr, transport);
    BTM_TRACE_API ("btm_sec_bond_by_transport BDA: %02x:%02x:%02x:%02x:%02x:%02x\n",
                   bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);

    BTM_TRACE_DEBUG("btm_sec_bond_by_transport: Transport used %d\n" , transport);


    /* Other security process is in progress */
    if (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE) {
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
        BTM_TRACE_ERROR ("BTM_SecBond: already busy in state: %s\n", btm_pair_state_descr(btm_cb.pairing_state));
#endif  ///BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE
        return (BTM_WRONG_MODE);
    }

    if ((p_dev_rec = btm_find_or_alloc_dev (bd_addr)) == NULL) {
        return (BTM_NO_RESOURCES);
    }

    BTM_TRACE_DEBUG ("before update sec_flags=0x%x\n", p_dev_rec->sec_flags);

    /* Finished if connection is active and already paired */
    if ( ((p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE) && transport == BT_TRANSPORT_BR_EDR
            &&  (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
#if (BLE_INCLUDED == TRUE)
            || ((p_dev_rec->ble_hci_handle != BTM_SEC_INVALID_HANDLE) && transport == BT_TRANSPORT_LE
                &&  (p_dev_rec->sec_flags & BTM_SEC_LE_AUTHENTICATED))
#endif

       ) {
        BTM_TRACE_WARNING("BTM_SecBond -> Already Paired\n");
        return (BTM_SUCCESS);
    }

    /* Tell controller to get rid of the link key if it has one stored */
    if ((BTM_DeleteStoredLinkKey (bd_addr, NULL)) != BTM_SUCCESS) {
        return (BTM_NO_RESOURCES);
    }

#if (CLASSIC_BT_INCLUDED == TRUE)
    /* Save the PIN code if we got a valid one */
    if (p_pin && (pin_len <= PIN_CODE_LEN) && (pin_len != 0)) {
        btm_cb.pin_code_len = pin_len;
        p_dev_rec->pin_code_length = pin_len;
        memcpy (btm_cb.pin_code, p_pin, PIN_CODE_LEN);
    }
#endif  ///CLASSIC_BT_INCLUDED == TRUE

    memcpy (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN);

    btm_cb.pairing_flags = BTM_PAIR_FLAGS_WE_STARTED_DD;

    p_dev_rec->security_required = BTM_SEC_OUT_AUTHENTICATE;
    p_dev_rec->is_originator     = TRUE;
    if (trusted_mask) {
        BTM_SEC_COPY_TRUSTED_DEVICE(trusted_mask, p_dev_rec->trusted_mask);
    }

#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    if (transport == BT_TRANSPORT_LE) {
        btm_ble_init_pseudo_addr (p_dev_rec, bd_addr);
        p_dev_rec->sec_flags &= ~ BTM_SEC_LE_MASK;

        if (SMP_Pair(bd_addr) == SMP_STARTED) {
            btm_cb.pairing_flags |= BTM_PAIR_FLAGS_LE_ACTIVE;
            p_dev_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
            return BTM_CMD_STARTED;
        }

        btm_cb.pairing_flags = 0;
        return (BTM_NO_RESOURCES);
    }
#endif

    p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED
                              | BTM_SEC_ROLE_SWITCHED  | BTM_SEC_LINK_KEY_AUTHED);


    BTM_TRACE_DEBUG ("after update sec_flags=0x%x\n", p_dev_rec->sec_flags);

#if (CLASSIC_BT_INCLUDED == TRUE)
    if (!controller_get_interface()->supports_simple_pairing()) {
        /* The special case when we authenticate keyboard.  Set pin type to fixed */
        /* It would be probably better to do it from the application, but it is */
        /* complicated */
        if (((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) == BTM_COD_MAJOR_PERIPHERAL)
                && (p_dev_rec->dev_class[2] & BTM_COD_MINOR_KEYBOARD)
                && (btm_cb.cfg.pin_type != HCI_PIN_TYPE_FIXED)) {
            btm_cb.pin_type_changed = TRUE;
            btsnd_hcic_write_pin_type (HCI_PIN_TYPE_FIXED);
        }
    }
#endif  ///CLASSIC_BT_INCLUDED == TRUE

    for (ii = 0; ii <= HCI_EXT_FEATURES_PAGE_MAX; ii++) {
#if (!CONFIG_BT_STACK_NO_LOG)
        p_features = p_dev_rec->features[ii];
#endif
        BTM_TRACE_EVENT("  remote_features page[%1d] = %02x-%02x-%02x-%02x\n",
                        ii, p_features[0], p_features[1], p_features[2], p_features[3]);
        BTM_TRACE_EVENT("                              %02x-%02x-%02x-%02x\n",
                        p_features[4], p_features[5], p_features[6], p_features[7]);
    }

    BTM_TRACE_EVENT ("BTM_SecBond: Remote sm4: 0x%x  HCI Handle: 0x%04x\n", p_dev_rec->sm4, p_dev_rec->hci_handle);

#if BTM_SEC_FORCE_RNR_FOR_DBOND == TRUE
    p_dev_rec->sec_flags &= ~BTM_SEC_NAME_KNOWN;
#endif

    /* If connection already exists... */
    if (p && p->hci_handle != BTM_SEC_INVALID_HANDLE) {
        if (!btm_sec_start_authentication (p_dev_rec)) {
            return (BTM_NO_RESOURCES);
        }

        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);

        /* Mark lcb as bonding */
        l2cu_update_lcb_4_bonding (bd_addr, TRUE);
        return (BTM_CMD_STARTED);
    }

    BTM_TRACE_DEBUG ("sec mode: %d sm4:x%x\n", btm_cb.security_mode, p_dev_rec->sm4);
    if (!controller_get_interface()->supports_simple_pairing()
            || (p_dev_rec->sm4 == BTM_SM4_KNOWN)) {
        if ( btm_sec_check_prefetch_pin (p_dev_rec) ) {
            return (BTM_CMD_STARTED);
        }
    }
    if ((btm_cb.security_mode == BTM_SEC_MODE_SP ||
            btm_cb.security_mode == BTM_SEC_MODE_SP_DEBUG ||
            btm_cb.security_mode == BTM_SEC_MODE_SC) &&
            BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4)) {
        /* local is 2.1 and peer is unknown */
        if ((p_dev_rec->sm4 & BTM_SM4_CONN_PEND) == 0) {
            /* we are not accepting connection request from peer
             * -> RNR (to learn if peer is 2.1)
             * RNR when no ACL causes HCI_RMT_HOST_SUP_FEAT_NOTIFY_EVT */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_GET_REM_NAME);
            BTM_ReadRemoteDeviceName(bd_addr, NULL, BT_TRANSPORT_BR_EDR);
        } else {
            /* We are accepting connection request from peer */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);
        }
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
        BTM_TRACE_DEBUG ("State:%s sm4: 0x%x sec_state:%d\n",
                         btm_pair_state_descr (btm_cb.pairing_state), p_dev_rec->sm4, p_dev_rec->sec_state);
#endif  ///BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE
        return BTM_CMD_STARTED;
    }

    /* both local and peer are 2.1  */
    status = btm_sec_dd_create_conn(p_dev_rec);

    if (status != BTM_CMD_STARTED) {
        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
    }

    return status;
}