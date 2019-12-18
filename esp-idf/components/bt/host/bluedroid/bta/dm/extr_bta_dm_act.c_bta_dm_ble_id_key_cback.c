#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_BLE_LOCAL_KEYS ;
struct TYPE_4__ {int /*<<< orphan*/  ble_id_keys; } ;
typedef  TYPE_1__ tBTA_DM_SEC ;
typedef  int UINT8 ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_sec_cback ) (int,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int) ; 
 int BTA_DM_BLE_LOCAL_ER_EVT ; 
 int BTA_DM_BLE_LOCAL_IR_EVT ; 
#define  BTM_BLE_KEY_TYPE_ER 129 
#define  BTM_BLE_KEY_TYPE_ID 128 
 TYPE_3__ bta_dm_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int,TYPE_1__*) ; 

__attribute__((used)) static void bta_dm_ble_id_key_cback (UINT8 key_type, tBTM_BLE_LOCAL_KEYS *p_key)
{
    UINT8   evt;
    tBTA_DM_SEC dm_key;

    switch (key_type) {
    case BTM_BLE_KEY_TYPE_ID:
    case BTM_BLE_KEY_TYPE_ER:
        if (bta_dm_cb.p_sec_cback) {
            memcpy(&dm_key.ble_id_keys, p_key, sizeof(tBTM_BLE_LOCAL_KEYS));

            evt = (key_type == BTM_BLE_KEY_TYPE_ID) ? BTA_DM_BLE_LOCAL_IR_EVT : \
                  BTA_DM_BLE_LOCAL_ER_EVT;
            bta_dm_cb.p_sec_cback(evt, &dm_key);
        }
        break;

    default:
        APPL_TRACE_DEBUG("Unknown key type %d", key_type);
        break;
    }
    return;

}