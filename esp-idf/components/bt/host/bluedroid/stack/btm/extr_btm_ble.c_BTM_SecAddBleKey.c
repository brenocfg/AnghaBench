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
typedef  int /*<<< orphan*/  tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  tBTM_LE_KEY_VALUE ;
typedef  scalar_t__ tBTM_LE_KEY_TYPE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_LE_KEY_LCSRK ; 
 scalar_t__ BTM_LE_KEY_LENC ; 
 scalar_t__ BTM_LE_KEY_LID ; 
 scalar_t__ BTM_LE_KEY_PCSRK ; 
 scalar_t__ BTM_LE_KEY_PENC ; 
 scalar_t__ BTM_LE_KEY_PID ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_resolving_list_load_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * btm_find_dev (int*) ; 
 int /*<<< orphan*/  btm_sec_save_le_key (int*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN BTM_SecAddBleKey (BD_ADDR bd_addr, tBTM_LE_KEY_VALUE *p_le_key, tBTM_LE_KEY_TYPE key_type)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    BTM_TRACE_DEBUG ("BTM_SecAddBleKey");
    p_dev_rec = btm_find_dev (bd_addr);
    if (!p_dev_rec || !p_le_key ||
            (key_type != BTM_LE_KEY_PENC && key_type != BTM_LE_KEY_PID &&
             key_type != BTM_LE_KEY_PCSRK && key_type != BTM_LE_KEY_LENC &&
             key_type != BTM_LE_KEY_LCSRK && key_type != BTM_LE_KEY_LID)) {
        BTM_TRACE_WARNING ("BTM_SecAddBleKey()  Wrong Type, or No Device record \
                        for bdaddr: %08x%04x, Type: %d",
                           (bd_addr[0] << 24) + (bd_addr[1] << 16) + (bd_addr[2] << 8) + bd_addr[3],
                           (bd_addr[4] << 8) + bd_addr[5], key_type);
        return (FALSE);
    }

    BTM_TRACE_DEBUG ("BTM_SecAddLeKey()  BDA: %08x%04x, Type: 0x%02x",
                     (bd_addr[0] << 24) + (bd_addr[1] << 16) + (bd_addr[2] << 8) + bd_addr[3],
                     (bd_addr[4] << 8) + bd_addr[5], key_type);

    btm_sec_save_le_key (bd_addr, key_type, p_le_key, FALSE);

#if (BLE_PRIVACY_SPT == TRUE)
    if (key_type == BTM_LE_KEY_PID || key_type == BTM_LE_KEY_LID) {
        btm_ble_resolving_list_load_dev (p_dev_rec);
    }
#endif


    return (TRUE);
}