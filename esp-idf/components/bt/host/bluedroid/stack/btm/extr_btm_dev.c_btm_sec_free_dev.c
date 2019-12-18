#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBT_TRANSPORT ;
struct TYPE_4__ {int sec_flags; int /*<<< orphan*/  link_key; void* bond_type; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;

/* Variables and functions */
 void* BOND_TYPE_UNKNOWN ; 
 int BTM_SEC_16_DIGIT_PIN_AUTHED ; 
 int BTM_SEC_AUTHENTICATED ; 
 int BTM_SEC_AUTHORIZED ; 
 int BTM_SEC_ENCRYPTED ; 
 int BTM_SEC_IN_USE ; 
 int BTM_SEC_LE_AUTHENTICATED ; 
 int BTM_SEC_LE_ENCRYPTED ; 
 int BTM_SEC_LE_LINK_KEY_AUTHED ; 
 int BTM_SEC_LE_LINK_KEY_KNOWN ; 
 int BTM_SEC_LE_NAME_KNOWN ; 
 int BTM_SEC_LINK_KEY_AUTHED ; 
 int BTM_SEC_LINK_KEY_KNOWN ; 
 int BTM_SEC_NAME_KNOWN ; 
 int BTM_SEC_ROLE_SWITCHED ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  LINK_KEY_LEN ; 
 int /*<<< orphan*/  btm_sec_clear_ble_keys (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_sec_free_dev (tBTM_SEC_DEV_REC *p_dev_rec, tBT_TRANSPORT transport)
{
    if (transport == BT_TRANSPORT_BR_EDR) {
        memset(p_dev_rec->link_key, 0, LINK_KEY_LEN);
        p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED
                                | BTM_SEC_ENCRYPTED | BTM_SEC_NAME_KNOWN
                                | BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_LINK_KEY_AUTHED
                                | BTM_SEC_ROLE_SWITCHED | BTM_SEC_16_DIGIT_PIN_AUTHED);
    } else if (transport == BT_TRANSPORT_LE) {
        p_dev_rec->bond_type = BOND_TYPE_UNKNOWN;
        p_dev_rec->sec_flags &= ~(BTM_SEC_LE_AUTHENTICATED | BTM_SEC_LE_ENCRYPTED
                                | BTM_SEC_LE_NAME_KNOWN | BTM_SEC_LE_LINK_KEY_KNOWN
                                | BTM_SEC_LE_LINK_KEY_AUTHED | BTM_SEC_ROLE_SWITCHED);
#if BLE_INCLUDED == TRUE
        /* Clear out any saved BLE keys */
        btm_sec_clear_ble_keys (p_dev_rec);
#endif
    } else {
        p_dev_rec->bond_type = BOND_TYPE_UNKNOWN;
        memset(p_dev_rec->link_key, 0, LINK_KEY_LEN);
        p_dev_rec->sec_flags = 0;

#if BLE_INCLUDED == TRUE
        /* Clear out any saved BLE keys */
        btm_sec_clear_ble_keys (p_dev_rec);
#endif
    }
    /* No BLE keys and BT keys, clear the sec_flags */
    if(p_dev_rec->sec_flags == BTM_SEC_IN_USE) {
        p_dev_rec->sec_flags = 0;
    }
}