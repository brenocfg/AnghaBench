#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int tGATT_SEC_ACTION ;
typedef  int /*<<< orphan*/  tBTM_BLE_SEC_ACT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_SEC_ENCRYPT ; 
 int /*<<< orphan*/  BTM_BLE_SEC_ENCRYPT_MITM ; 
 int /*<<< orphan*/  BTM_BLE_SEC_ENCRYPT_NO_MITM ; 
 int /*<<< orphan*/  FALSE ; 
#define  GATT_SEC_ENCRYPT 130 
#define  GATT_SEC_ENCRYPT_MITM 129 
#define  GATT_SEC_ENCRYPT_NO_MITM 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN gatt_convert_sec_action(tGATT_SEC_ACTION gatt_sec_act, tBTM_BLE_SEC_ACT *p_btm_sec_act )
{
    BOOLEAN status = TRUE;
    switch (gatt_sec_act) {
    case GATT_SEC_ENCRYPT:
        *p_btm_sec_act = BTM_BLE_SEC_ENCRYPT;
        break;
    case GATT_SEC_ENCRYPT_NO_MITM:
        *p_btm_sec_act = BTM_BLE_SEC_ENCRYPT_NO_MITM;
        break;
    case GATT_SEC_ENCRYPT_MITM:
        *p_btm_sec_act = BTM_BLE_SEC_ENCRYPT_MITM;
        break;
    default:
        status = FALSE;
        break;
    }

    return status;
}