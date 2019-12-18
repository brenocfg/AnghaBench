#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ transport; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  scalar_t__ tGATT_SEC_ACTION ;
struct TYPE_5__ {int auth_req; scalar_t__ operation; scalar_t__ op_subtype; TYPE_1__* p_tcb; } ;
typedef  TYPE_2__ tGATT_CLCB ;
typedef  int tGATT_AUTH_REQ ;
typedef  scalar_t__ tBTM_BLE_SEC_REQ_ACT ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_BLE_SEC_REQ_ACT_DISCARD ; 
 int /*<<< orphan*/  BTM_GetSecurityFlagsByTransport (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int BTM_LE_KEY_LCSRK ; 
 scalar_t__ BTM_LE_SEC_NONE ; 
 int BTM_SEC_FLAG_ENCRYPTED ; 
 int BTM_SEC_FLAG_LKEY_AUTHED ; 
 int BTM_SEC_FLAG_LKEY_KNOWN ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATTC_OPTYPE_WRITE ; 
#define  GATT_AUTH_REQ_MITM 131 
 int GATT_AUTH_REQ_NONE ; 
#define  GATT_AUTH_REQ_NO_MITM 130 
#define  GATT_AUTH_REQ_SIGNED_MITM 129 
#define  GATT_AUTH_REQ_SIGNED_NO_MITM 128 
 scalar_t__ GATT_SEC_ENCRYPT ; 
 scalar_t__ GATT_SEC_ENCRYPT_MITM ; 
 scalar_t__ GATT_SEC_ENCRYPT_NO_MITM ; 
 scalar_t__ GATT_SEC_ENC_PENDING ; 
 scalar_t__ GATT_SEC_OK ; 
 scalar_t__ GATT_SEC_SIGN_DATA ; 
 scalar_t__ GATT_WRITE_NO_RSP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_get_enc_key_type (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  btm_ble_link_sec_check (int /*<<< orphan*/ ,int,scalar_t__*) ; 

tGATT_SEC_ACTION gatt_determine_sec_act(tGATT_CLCB *p_clcb )
{
    tGATT_SEC_ACTION    act = GATT_SEC_OK;
    UINT8               sec_flag;
    tGATT_TCB           *p_tcb = p_clcb->p_tcb;
    tGATT_AUTH_REQ      auth_req = p_clcb->auth_req;
    BOOLEAN             is_link_encrypted = FALSE;
    BOOLEAN             is_link_key_known = FALSE;
    BOOLEAN             is_key_mitm = FALSE;
#if (SMP_INCLUDED == TRUE)
    UINT8               key_type;
    tBTM_BLE_SEC_REQ_ACT    sec_act = BTM_LE_SEC_NONE;
#endif  ///SMP_INCLUDED == TRUE
    if (auth_req == GATT_AUTH_REQ_NONE ) {
        return act;
    }

    BTM_GetSecurityFlagsByTransport(p_tcb->peer_bda, &sec_flag, p_clcb->p_tcb->transport);
#if (SMP_INCLUDED == TRUE)
    btm_ble_link_sec_check(p_tcb->peer_bda, auth_req, &sec_act);
#endif  ///SMP_INCLUDED == TRUE
    /* if a encryption is pending, need to wait */
    if (
#if (SMP_INCLUDED == TRUE)
    sec_act == BTM_BLE_SEC_REQ_ACT_DISCARD &&
#endif  ///SMP_INCLUDED == TRUE
            auth_req != GATT_AUTH_REQ_NONE) {
        return GATT_SEC_ENC_PENDING;
    }

    if (sec_flag & (BTM_SEC_FLAG_ENCRYPTED | BTM_SEC_FLAG_LKEY_KNOWN)) {
        if (sec_flag & BTM_SEC_FLAG_ENCRYPTED) {
            is_link_encrypted = TRUE;
        }

        is_link_key_known = TRUE;

        if (sec_flag & BTM_SEC_FLAG_LKEY_AUTHED) {
            is_key_mitm = TRUE;
        }
    }

    /* first check link key upgrade required or not */
    switch (auth_req) {
    case GATT_AUTH_REQ_MITM:
    case GATT_AUTH_REQ_SIGNED_MITM:
        if (!is_key_mitm) {
            act = GATT_SEC_ENCRYPT_MITM;
        }
        break;

    case GATT_AUTH_REQ_NO_MITM:
    case GATT_AUTH_REQ_SIGNED_NO_MITM:
        if (!is_link_key_known) {
            act = GATT_SEC_ENCRYPT_NO_MITM;
        }
        break;
    default:
        break;
    }

    /* now check link needs to be encrypted or not if the link key upgrade is not required */
    if (act == GATT_SEC_OK) {
        if (p_tcb->transport == BT_TRANSPORT_LE &&
                (p_clcb->operation == GATTC_OPTYPE_WRITE) &&
                (p_clcb->op_subtype == GATT_WRITE_NO_RSP)) {
            /* this is a write command request
               check data signing required or not */
            if (!is_link_encrypted) {
#if (SMP_INCLUDED == TRUE)
                btm_ble_get_enc_key_type(p_tcb->peer_bda, &key_type);
#endif  ///SMP_INCLUDED == TRUE
                if (
#if (SMP_INCLUDED == TRUE)
                    (key_type & BTM_LE_KEY_LCSRK) &&
#endif  ///SMP_INCLUDED == TRUE
                        ((auth_req == GATT_AUTH_REQ_SIGNED_NO_MITM) ||
                         (auth_req == GATT_AUTH_REQ_SIGNED_MITM))) {
                    act = GATT_SEC_SIGN_DATA;
                } else {
                    act = GATT_SEC_ENCRYPT;
                }
            }
        } else {
            if (!is_link_encrypted) {
                act = GATT_SEC_ENCRYPT;
            }
        }

    }

    return  act ;

}