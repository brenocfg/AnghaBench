#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ ble_hci_handle; int sm4; int* bd_addr; int sec_flags; scalar_t__ link_key_type; int pin_code_length; int /*<<< orphan*/  is_originator; void* link_key_changed; int /*<<< orphan*/  sec_bd_name; int /*<<< orphan*/  dev_class; scalar_t__ hci_handle; int /*<<< orphan*/  security_required; void* link_key_not_sent; void* rs_disc_pending; int /*<<< orphan*/  device_type; scalar_t__ timestamp; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
struct TYPE_16__ {int /*<<< orphan*/  remote_addr; } ;
typedef  TYPE_3__ tACL_CONN ;
typedef  int UINT8 ;
typedef  void* UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_17__ {void* param; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* p_auth_complete_callback ) (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_13__ {scalar_t__ pairing_state; int pairing_flags; int acl_disc_reason; scalar_t__ security_mode; scalar_t__ btm_def_link_policy; int /*<<< orphan*/  btm_acl_pkt_types_supported; TYPE_1__ api; TYPE_4__ sec_collision_tle; TYPE_2__* p_collided_dev_rec; int /*<<< orphan*/  pairing_bda; int /*<<< orphan*/  dev_rec_count; } ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_CMD_STARTED ; 
 int BTM_DEVICE_TIMEOUT ; 
 int BTM_ERR_PROCESSING ; 
 scalar_t__ BTM_LKEY_TYPE_AUTH_COMB ; 
 scalar_t__ BTM_LKEY_TYPE_AUTH_COMB_P_256 ; 
 scalar_t__ BTM_LKEY_TYPE_REMOTE_UNIT ; 
 int BTM_PAIR_FLAGS_REJECTED_CONNECT ; 
 int BTM_PAIR_FLAGS_WE_STARTED_DD ; 
 scalar_t__ BTM_PAIR_STATE_GET_REM_NAME ; 
 scalar_t__ BTM_PAIR_STATE_IDLE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_LOCAL_PIN ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_PIN_REQ ; 
 int /*<<< orphan*/  BTM_ReadRemoteDeviceName (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int BTM_SEC_16_DIGIT_PIN_AUTHED ; 
 int BTM_SEC_AUTHENTICATED ; 
 int BTM_SEC_AUTHORIZED ; 
 int BTM_SEC_ENCRYPTED ; 
 scalar_t__ BTM_SEC_IS_SM4_UNKNOWN (int) ; 
 int BTM_SEC_LE_LINK_KEY_KNOWN ; 
 int BTM_SEC_LINK_KEY_AUTHED ; 
 int BTM_SEC_LINK_KEY_KNOWN ; 
 scalar_t__ BTM_SEC_MODE_LINK ; 
 int BTM_SEC_NAME_KNOWN ; 
 int /*<<< orphan*/  BTM_SEC_OUT_AUTHENTICATE ; 
 int BTM_SEC_ROLE_SWITCHED ; 
 void* BTM_SEC_RS_NOT_PENDING ; 
 int BTM_SM4_CONN_PEND ; 
 int /*<<< orphan*/  BTM_SetLinkPolicy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,scalar_t__,int,int,int,...) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,...) ; 
 int /*<<< orphan*/  BTU_TTYPE_USER_FUNC ; 
 int /*<<< orphan*/  BT_DEVICE_TYPE_BREDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 void* FALSE ; 
 int HCI_ENCRYPT_MODE_DISABLED ; 
 int HCI_ERR_AUTH_FAILURE ; 
 int HCI_ERR_CONNECTION_EXISTS ; 
 int HCI_ERR_CONNECTION_TOUT ; 
 int HCI_ERR_ENCRY_MODE_NOT_ACCEPTABLE ; 
 int HCI_ERR_HOST_REJECT_DEVICE ; 
 int HCI_ERR_HOST_REJECT_SECURITY ; 
 int HCI_ERR_KEY_MISSING ; 
 int HCI_ERR_LMP_RESPONSE_TIMEOUT ; 
 int HCI_ERR_PAGE_TIMEOUT ; 
 int HCI_ERR_PAIRING_NOT_ALLOWED ; 
 int HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED ; 
 int HCI_ERR_REPEATED_ATTEMPTS ; 
 int HCI_ERR_UNIT_KEY_USED ; 
 int HCI_ERR_UNSPECIFIED ; 
 int /*<<< orphan*/  HCI_ROLE_SLAVE ; 
 int HCI_SUCCESS ; 
 void* TRUE ; 
 int /*<<< orphan*/  btm_acl_created (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_acl_resubmit_page () ; 
 TYPE_3__* btm_bda_to_acl (int*,int /*<<< orphan*/ ) ; 
 TYPE_11__ btm_cb ; 
 TYPE_2__* btm_find_dev (int*) ; 
 int /*<<< orphan*/  btm_pair_state_descr (scalar_t__) ; 
 int /*<<< orphan*/  btm_restore_mode () ; 
 TYPE_2__* btm_sec_alloc_dev (int*) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (scalar_t__) ; 
 scalar_t__ btm_sec_connect_after_reject_timeout ; 
 int /*<<< orphan*/  btm_sec_dev_rec_cback_event (TYPE_2__*,int,void*) ; 
 int btm_sec_execute_procedure (TYPE_2__*) ; 
 int /*<<< orphan*/  btm_send_link_key_notif (TYPE_2__*) ; 
 int /*<<< orphan*/  btm_set_packet_types (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_update_lcb_4_bonding (int*,void*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void btm_sec_connected (UINT8 *bda, UINT16 handle, UINT8 status, UINT8 enc_mode)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bda);
    UINT8            res;
    BOOLEAN          is_pairing_device = FALSE;
    tACL_CONN        *p_acl_cb;
    UINT8            bit_shift = 0;

    btm_acl_resubmit_page();

    /* Commenting out trace due to obf/compilation problems.
    */
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
    if (p_dev_rec) {
        BTM_TRACE_EVENT ("Security Manager: btm_sec_connected in state: %s  handle:%d status:%d enc_mode:%d  bda:%x RName:%s\n",
                         btm_pair_state_descr(btm_cb.pairing_state), handle, status, enc_mode,
                         (bda[2] << 24) + (bda[3] << 16) + (bda[4] << 8) + bda[5],
                         p_dev_rec->sec_bd_name);
    } else {
        BTM_TRACE_EVENT ("Security Manager: btm_sec_connected in state: %s  handle:%d status:%d enc_mode:%d  bda:%x \n",
                         btm_pair_state_descr(btm_cb.pairing_state), handle, status, enc_mode,
                         (bda[2] << 24) + (bda[3] << 16) + (bda[4] << 8) + bda[5]);
    }
#endif

    if (!p_dev_rec) {
        /* There is no device record for new connection.  Allocate one */
        if (status == HCI_SUCCESS) {
            p_dev_rec = btm_sec_alloc_dev (bda);
        } else {
            /* If the device matches with stored paring address
             * reset the paring state to idle */
            if ((btm_cb.pairing_state != BTM_PAIR_STATE_IDLE) &&
                    (memcmp (btm_cb.pairing_bda, bda, BD_ADDR_LEN) == 0)) {
                btm_sec_change_pairing_state(BTM_PAIR_STATE_IDLE);
            }

            /* can not find the device record and the status is error,
             * just ignore it */
            return;
        }
    } else { /* Update the timestamp for this device */

#if BLE_INCLUDED == TRUE
        bit_shift = (handle == p_dev_rec->ble_hci_handle) ? 8 : 0;
#endif
        p_dev_rec->timestamp = btm_cb.dev_rec_count++;
        if (p_dev_rec->sm4 & BTM_SM4_CONN_PEND) {
            /* tell L2CAP it's a bonding connection. */
            if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
                    &&  (memcmp (btm_cb.pairing_bda, p_dev_rec->bd_addr, BD_ADDR_LEN) == 0)
                    &&  (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) ) {
                /* if incoming connection failed while pairing, then try to connect and continue */
                /* Motorola S9 disconnects without asking pin code */
                if ((status != HCI_SUCCESS) && (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_PIN_REQ)) {
                    BTM_TRACE_WARNING ("Security Manager: btm_sec_connected: incoming connection failed without asking PIN\n");

                    p_dev_rec->sm4 &= ~BTM_SM4_CONN_PEND;
                    if (p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN) {
                        /* Start timer with 0 to initiate connection with new LCB */
                        /* because L2CAP will delete current LCB with this event  */
                        btm_cb.p_collided_dev_rec = p_dev_rec;
                        btm_cb.sec_collision_tle.param = (UINT32) btm_sec_connect_after_reject_timeout;
                        btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, 0);
                    } else {
                        btm_sec_change_pairing_state (BTM_PAIR_STATE_GET_REM_NAME);
                        BTM_ReadRemoteDeviceName(p_dev_rec->bd_addr, NULL, BT_TRANSPORT_BR_EDR);
                    }
#if BTM_DISC_DURING_RS == TRUE
                    p_dev_rec->rs_disc_pending   = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
#endif
                    return;
                } else {
                    l2cu_update_lcb_4_bonding(p_dev_rec->bd_addr, TRUE);
                }
            }
            /* always clear the pending flag */
            p_dev_rec->sm4 &= ~BTM_SM4_CONN_PEND;
        }
    }

#if BLE_INCLUDED == TRUE
    p_dev_rec->device_type |= BT_DEVICE_TYPE_BREDR;
#endif

#if BTM_DISC_DURING_RS == TRUE
    p_dev_rec->rs_disc_pending   = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
#endif

    p_dev_rec->rs_disc_pending   = BTM_SEC_RS_NOT_PENDING;     /* reset flag */

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
            && (memcmp (btm_cb.pairing_bda, bda, BD_ADDR_LEN) == 0) ) {
        /* if we rejected incoming connection from bonding device */
        if ((status == HCI_ERR_HOST_REJECT_DEVICE)
                && (btm_cb.pairing_flags & BTM_PAIR_FLAGS_REJECTED_CONNECT)) {
            BTM_TRACE_WARNING ("Security Manager: btm_sec_connected: HCI_Conn_Comp Flags:0x%04x, sm4: 0x%x\n",
                               btm_cb.pairing_flags, p_dev_rec->sm4);

            btm_cb.pairing_flags &= ~BTM_PAIR_FLAGS_REJECTED_CONNECT;
            if (BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4)) {
                /* Try again: RNR when no ACL causes HCI_RMT_HOST_SUP_FEAT_NOTIFY_EVT */
                btm_sec_change_pairing_state (BTM_PAIR_STATE_GET_REM_NAME);
                BTM_ReadRemoteDeviceName(bda, NULL, BT_TRANSPORT_BR_EDR);
                return;
            }

            /* if we already have pin code */
            if (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_LOCAL_PIN) {
                /* Start timer with 0 to initiate connection with new LCB */
                /* because L2CAP will delete current LCB with this event  */
                btm_cb.p_collided_dev_rec = p_dev_rec;
                btm_cb.sec_collision_tle.param = (UINT32) btm_sec_connect_after_reject_timeout;
                btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, 0);
            }

            return;
        }
        /* wait for incoming connection without resetting pairing state */
        else if (status == HCI_ERR_CONNECTION_EXISTS) {
            BTM_TRACE_WARNING ("Security Manager: btm_sec_connected: Wait for incoming connection\n");
            return;
        }

        is_pairing_device = TRUE;
    }

    /* If connection was made to do bonding restore link security if changed */
    btm_restore_mode();

    /* if connection fails during pin request, notify application */
    if (status != HCI_SUCCESS) {
        /* If connection failed because of during pairing, need to tell user */
        if (is_pairing_device) {
            p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;
            p_dev_rec->sec_flags &= ~((BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_LINK_KEY_AUTHED) << bit_shift);
            BTM_TRACE_DEBUG ("security_required:%x \n", p_dev_rec->security_required );

            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

            /* We need to notify host that the key is not known any more */
            if (btm_cb.api.p_auth_complete_callback) {
                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                        p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, status);
            }
        }
        /*
            Do not send authentication failure, if following conditions hold good
             1.  BTM Sec Pairing state is idle
             2.  Link key for the remote device is present.
             3.  Remote is SSP capable.
         */
        else if  ((p_dev_rec->link_key_type  <= BTM_LKEY_TYPE_REMOTE_UNIT) &&
                  (((status == HCI_ERR_AUTH_FAILURE)                      ||
                    (status == HCI_ERR_KEY_MISSING)                         ||
                    (status == HCI_ERR_HOST_REJECT_SECURITY)                ||
                    (status == HCI_ERR_PAIRING_NOT_ALLOWED)                 ||
                    (status == HCI_ERR_UNIT_KEY_USED)                       ||
                    (status == HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED) ||
                    (status == HCI_ERR_ENCRY_MODE_NOT_ACCEPTABLE)           ||
                    (status == HCI_ERR_REPEATED_ATTEMPTS)))) {
            p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;
            p_dev_rec->sec_flags &= ~ (BTM_SEC_LE_LINK_KEY_KNOWN << bit_shift);


#ifdef BRCM_NOT_4_BTE
            /* If we rejected pairing, pass this special result code */
            if (btm_cb.acl_disc_reason == HCI_ERR_HOST_REJECT_SECURITY) {
                status = HCI_ERR_HOST_REJECT_SECURITY;
            }
#endif

            /* We need to notify host that the key is not known any more */
            if (btm_cb.api.p_auth_complete_callback) {
                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                        p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, status);
            }
        }

        if (status == HCI_ERR_CONNECTION_TOUT || status == HCI_ERR_LMP_RESPONSE_TIMEOUT  ||
                status == HCI_ERR_UNSPECIFIED     || status == HCI_ERR_PAGE_TIMEOUT) {
            btm_sec_dev_rec_cback_event (p_dev_rec, BTM_DEVICE_TIMEOUT, FALSE);
        } else {
            btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING, FALSE);
        }

        return;
    }

    /* If initiated dedicated bonding, return the link key now, and initiate disconnect */
    /* If dedicated bonding, and we now have a link key, we are all done */
    if ( is_pairing_device
            && (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN) ) {
        if (p_dev_rec->link_key_not_sent) {
            p_dev_rec->link_key_not_sent = FALSE;
            btm_send_link_key_notif(p_dev_rec);
        }

        p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;

        /* remember flag before it is initialized */
        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) {
            res = TRUE;
        } else {
            res = FALSE;
        }

        if (btm_cb.api.p_auth_complete_callback) {
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                    p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_SUCCESS);
        }

        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

        if ( res ) {
            /* Let l2cap start bond timer */
            l2cu_update_lcb_4_bonding (p_dev_rec->bd_addr, TRUE);
        }

        return;
    }

    p_dev_rec->hci_handle = handle;

    /* role may not be correct here, it will be updated by l2cap, but we need to */
    /* notify btm_acl that link is up, so starting of rmt name request will not */
    /* set paging flag up */
    p_acl_cb = btm_bda_to_acl(bda, BT_TRANSPORT_BR_EDR);
    if (p_acl_cb) {
        /* whatever is in btm_establish_continue() without reporting the BTM_BL_CONN_EVT event */
#if (!defined(BTM_BYPASS_EXTRA_ACL_SETUP) || BTM_BYPASS_EXTRA_ACL_SETUP == FALSE)
        /* For now there are a some devices that do not like sending */
        /* commands events and data at the same time. */
        /* Set the packet types to the default allowed by the device */
        btm_set_packet_types (p_acl_cb, btm_cb.btm_acl_pkt_types_supported);

        if (btm_cb.btm_def_link_policy) {
            BTM_SetLinkPolicy (p_acl_cb->remote_addr, &btm_cb.btm_def_link_policy);
        }
#endif
    }
    btm_acl_created (bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name, handle, HCI_ROLE_SLAVE, BT_TRANSPORT_BR_EDR);

    /* Initialize security flags.  We need to do that because some            */
    /* authorization complete could have come after the connection is dropped */
    /* and that would set wrong flag that link has been authorized already    */
    p_dev_rec->sec_flags &= ~((BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED |
                               BTM_SEC_ENCRYPTED | BTM_SEC_ROLE_SWITCHED) << bit_shift);

    if (enc_mode != HCI_ENCRYPT_MODE_DISABLED) {
        p_dev_rec->sec_flags |= ((BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED) << bit_shift);
    }

    if (btm_cb.security_mode == BTM_SEC_MODE_LINK) {
        p_dev_rec->sec_flags |= (BTM_SEC_AUTHENTICATED << bit_shift);
    }

    if (p_dev_rec->pin_code_length >= 16 ||
            p_dev_rec->link_key_type == BTM_LKEY_TYPE_AUTH_COMB ||
            p_dev_rec->link_key_type == BTM_LKEY_TYPE_AUTH_COMB_P_256) {
        p_dev_rec->sec_flags |= (BTM_SEC_16_DIGIT_PIN_AUTHED << bit_shift);
    }

    p_dev_rec->link_key_changed = FALSE;

    /* After connection is established we perform security if we do not know */
    /* the name, or if we are originator because some procedure can have */
    /* been scheduled while connection was down */
    BTM_TRACE_DEBUG ("is_originator:%d \n", p_dev_rec->is_originator);
    if (!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN) || p_dev_rec->is_originator) {
        if ((res = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED) {
            btm_sec_dev_rec_cback_event (p_dev_rec, res, FALSE);
        }
    }
    return;
}