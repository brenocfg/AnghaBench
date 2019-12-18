#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  pltk; int /*<<< orphan*/  ediv; TYPE_5__ rand; } ;
struct TYPE_10__ {int key_type; TYPE_1__ keys; } ;
struct TYPE_11__ {scalar_t__ sec_state; TYPE_2__ ble; int /*<<< orphan*/  ble_hci_handle; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
struct TYPE_12__ {int /*<<< orphan*/  enc_handle; } ;
typedef  TYPE_4__ tBTM_CB ;
typedef  TYPE_5__ BT_OCTET8 ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_BUSY ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int BTM_LE_KEY_PENC ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 scalar_t__ BTM_SEC_STATE_ENCRYPTING ; 
 scalar_t__ BTM_SEC_STATE_IDLE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*) ; 
 scalar_t__ BTM_WRONG_MODE ; 
 TYPE_4__ btm_cb ; 
 TYPE_3__* btm_find_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ btsnd_hcic_ble_start_enc (int /*<<< orphan*/ ,TYPE_5__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_STATUS btm_ble_start_encrypt(BD_ADDR bda, BOOLEAN use_stk, BT_OCTET16 stk)
{
#if (SMP_INCLUDED == TRUE)
    tBTM_CB *p_cb = &btm_cb;
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bda);
    BT_OCTET8    dummy_rand = {0};
#endif  ///SMP_INCLUDED == TRUE

    tBTM_STATUS  rt = BTM_NO_RESOURCES;
#if (SMP_INCLUDED == TRUE)
    BTM_TRACE_DEBUG ("btm_ble_start_encrypt");

    if (!p_rec ) {
        BTM_TRACE_ERROR("Link is not active, can not encrypt!");
        return BTM_WRONG_MODE;
    }

    if (p_rec->sec_state == BTM_SEC_STATE_ENCRYPTING) {
        BTM_TRACE_WARNING("Link Encryption is active, Busy!");
        return BTM_BUSY;
    }

    p_cb->enc_handle = p_rec->ble_hci_handle;

    if (use_stk) {
        if (btsnd_hcic_ble_start_enc(p_rec->ble_hci_handle, dummy_rand, 0, stk)) {
            rt = BTM_CMD_STARTED;
        }
    } else if (p_rec->ble.key_type & BTM_LE_KEY_PENC) {
        if (btsnd_hcic_ble_start_enc(p_rec->ble_hci_handle, p_rec->ble.keys.rand,
                                     p_rec->ble.keys.ediv, p_rec->ble.keys.pltk)) {
            rt = BTM_CMD_STARTED;
        }
    } else {
        BTM_TRACE_ERROR("No key available to encrypt the link");
    }
    if (rt == BTM_CMD_STARTED) {
        if (p_rec->sec_state == BTM_SEC_STATE_IDLE) {
            p_rec->sec_state = BTM_SEC_STATE_ENCRYPTING;
        }
    }
#endif  ///SMP_INCLUDED == TRUE
    return rt;
}