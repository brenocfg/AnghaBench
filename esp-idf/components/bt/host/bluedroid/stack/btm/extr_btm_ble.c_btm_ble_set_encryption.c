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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_4__ {int key_type; int skip_update_conn_param; } ;
struct TYPE_5__ {int /*<<< orphan*/  sec_state; TYPE_1__ ble; int /*<<< orphan*/  security_required; int /*<<< orphan*/  role_master; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int tBTM_LE_AUTH_REQ ;
typedef  int /*<<< orphan*/  tBTM_BLE_SEC_REQ_ACT ;
typedef  int tBTM_BLE_SEC_ACT ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
#define  BTM_BLE_SEC_ENCRYPT 130 
#define  BTM_BLE_SEC_ENCRYPT_MITM 129 
#define  BTM_BLE_SEC_ENCRYPT_NO_MITM 128 
 int /*<<< orphan*/  BTM_BLE_SEC_REQ_ACT_ENCRYPT ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int BTM_LE_KEY_PENC ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_ROLE_MASTER ; 
 int /*<<< orphan*/  BTM_ROLE_SLAVE ; 
 int /*<<< orphan*/  BTM_SEC_IN_MITM ; 
 int /*<<< orphan*/  BTM_SEC_STATE_AUTHENTICATING ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,int) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 int /*<<< orphan*/  FALSE ; 
 int SMP_AUTH_GEN_BOND ; 
 int SMP_AUTH_YN_BIT ; 
 int /*<<< orphan*/  SMP_Pair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_STARTED ; 
 int /*<<< orphan*/  btm_ble_link_sec_check (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_ble_start_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* btm_find_dev (int /*<<< orphan*/ ) ; 

tBTM_STATUS btm_ble_set_encryption (BD_ADDR bd_addr, void *p_ref_data, UINT8 link_role)
{
    tBTM_STATUS         cmd = BTM_NO_RESOURCES;
#if (SMP_INCLUDED == TRUE)
    tBTM_BLE_SEC_ACT    sec_act = *(tBTM_BLE_SEC_ACT *)p_ref_data ;
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bd_addr);
    tBTM_BLE_SEC_REQ_ACT sec_req_act;
    tBTM_LE_AUTH_REQ    auth_req;

    if (p_rec == NULL) {
        BTM_TRACE_WARNING ("btm_ble_set_encryption (NULL device record!! sec_act=0x%x", sec_act);
        return (BTM_WRONG_MODE);
    }

    BTM_TRACE_DEBUG ("btm_ble_set_encryption sec_act=0x%x role_master=%d", sec_act, p_rec->role_master);

    if (sec_act == BTM_BLE_SEC_ENCRYPT_MITM) {
        p_rec->security_required |= BTM_SEC_IN_MITM;
    }

    switch (sec_act) {
    case BTM_BLE_SEC_ENCRYPT:
        if (link_role == BTM_ROLE_MASTER && (p_rec->ble.key_type & BTM_LE_KEY_PENC)) {
            /* start link layer encryption using the security info stored */
            cmd = btm_ble_start_encrypt(bd_addr, FALSE, NULL);
            break;
        }
    /* if salve role then fall through to call SMP_Pair below which will send a
       sec_request to request the master to encrypt the link */
    case BTM_BLE_SEC_ENCRYPT_NO_MITM:
    case BTM_BLE_SEC_ENCRYPT_MITM:
        if ((link_role == BTM_ROLE_MASTER) && (sec_act != BTM_BLE_SEC_ENCRYPT)) {
            auth_req = (sec_act == BTM_BLE_SEC_ENCRYPT_NO_MITM)
                       ? SMP_AUTH_GEN_BOND : (SMP_AUTH_GEN_BOND | SMP_AUTH_YN_BIT);
            btm_ble_link_sec_check (bd_addr, auth_req, &sec_req_act);

            if (sec_req_act == BTM_BLE_SEC_REQ_ACT_ENCRYPT) {
                cmd = btm_ble_start_encrypt(bd_addr, FALSE, NULL);
                break;
            }
        }
#if (SMP_SLAVE_CON_PARAMS_UPD_ENABLE == TRUE)
        // already have encrypted information, do not need to update connection parameters
        if(link_role == BTM_ROLE_SLAVE && (p_rec->ble.key_type & BTM_LE_KEY_PENC)) {
            p_rec->ble.skip_update_conn_param = true;
        } else {
            p_rec->ble.skip_update_conn_param = false;
        }
#endif
        if (SMP_Pair(bd_addr) == SMP_STARTED) {
            cmd = BTM_CMD_STARTED;
            p_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;
        }
        break;

    default:
        cmd = BTM_WRONG_MODE;
        break;
    }
#endif  ///SMP_INCLUDED == TRUE
    return cmd;
}