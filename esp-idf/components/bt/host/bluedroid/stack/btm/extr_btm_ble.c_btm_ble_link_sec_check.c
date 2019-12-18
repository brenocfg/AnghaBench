#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sec_level; } ;
struct TYPE_6__ {int key_type; TYPE_1__ keys; } ;
struct TYPE_7__ {scalar_t__ sec_state; int sec_flags; TYPE_2__ ble; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  int tBTM_LE_AUTH_REQ ;
typedef  int /*<<< orphan*/  tBTM_BLE_SEC_REQ_ACT ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_SEC_REQ_ACT_DISCARD ; 
 int /*<<< orphan*/  BTM_BLE_SEC_REQ_ACT_ENCRYPT ; 
 int /*<<< orphan*/  BTM_BLE_SEC_REQ_ACT_PAIR ; 
 int BTM_LE_AUTH_REQ_MITM ; 
 int BTM_LE_KEY_PENC ; 
 scalar_t__ BTM_LE_SEC_AUTHENTICATED ; 
 scalar_t__ BTM_LE_SEC_NONE ; 
 scalar_t__ BTM_LE_SEC_UNAUTHENTICATE ; 
 int BTM_SEC_LE_AUTHENTICATED ; 
 int BTM_SEC_LE_ENCRYPTED ; 
 scalar_t__ BTM_SEC_STATE_AUTHENTICATING ; 
 scalar_t__ BTM_SEC_STATE_ENCRYPTING ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 TYPE_3__* btm_find_dev (int /*<<< orphan*/ ) ; 

void btm_ble_link_sec_check(BD_ADDR bd_addr, tBTM_LE_AUTH_REQ auth_req, tBTM_BLE_SEC_REQ_ACT *p_sec_req_act)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bd_addr);
    UINT8 req_sec_level = BTM_LE_SEC_NONE, cur_sec_level = BTM_LE_SEC_NONE;

    BTM_TRACE_DEBUG ("btm_ble_link_sec_check auth_req =0x%x", auth_req);

    if (p_dev_rec == NULL) {
        BTM_TRACE_ERROR ("btm_ble_link_sec_check received for unknown device");
        return;
    }

    if (p_dev_rec->sec_state == BTM_SEC_STATE_ENCRYPTING ||
            p_dev_rec->sec_state == BTM_SEC_STATE_AUTHENTICATING) {
        /* race condition: discard the security request while master is encrypting the link */
        *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_DISCARD;
    } else {
        req_sec_level = BTM_LE_SEC_UNAUTHENTICATE;
        if (auth_req & BTM_LE_AUTH_REQ_MITM) {
            req_sec_level = BTM_LE_SEC_AUTHENTICATED;
        }

        BTM_TRACE_DEBUG ("dev_rec sec_flags=0x%x", p_dev_rec->sec_flags);

        /* currently encrpted  */
        if (p_dev_rec->sec_flags & BTM_SEC_LE_ENCRYPTED) {
            if (p_dev_rec->sec_flags & BTM_SEC_LE_AUTHENTICATED) {
                cur_sec_level = BTM_LE_SEC_AUTHENTICATED;
            } else {
                cur_sec_level = BTM_LE_SEC_UNAUTHENTICATE;
            }
        } else { /* unencrypted link */
            /* if bonded, get the key security level */
            if (p_dev_rec->ble.key_type & BTM_LE_KEY_PENC) {
                cur_sec_level = p_dev_rec->ble.keys.sec_level;
            } else {
                cur_sec_level = BTM_LE_SEC_NONE;
            }
        }

        if (cur_sec_level >= req_sec_level) {
            /* To avoid re-encryption on an encrypted link for an equal condition encryption */
            *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_ENCRYPT;
        } else {
            *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_PAIR; /* start the pariring process to upgrade the keys*/
        }
    }

    BTM_TRACE_DEBUG("cur_sec_level=%d req_sec_level=%d sec_req_act=%d",
                    cur_sec_level,
                    req_sec_level,
                    *p_sec_req_act);


}