#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_BLE_LOCAL_KEYS ;
typedef  int UINT8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_le_key_callback ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ble_encryption_key_value; int /*<<< orphan*/  id_keys; } ;
struct TYPE_6__ {TYPE_1__ api; TYPE_2__ devcb; } ;

/* Variables and functions */
#define  BTM_BLE_KEY_TYPE_ER 129 
#define  BTM_BLE_KEY_TYPE_ID 128 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btm_notify_new_key(UINT8 key_type)
{
    tBTM_BLE_LOCAL_KEYS *p_locak_keys = NULL;

    BTM_TRACE_DEBUG ("btm_notify_new_key key_type=%d", key_type);

    if (btm_cb.api.p_le_key_callback) {
        switch (key_type) {
        case BTM_BLE_KEY_TYPE_ID:
            BTM_TRACE_DEBUG ("BTM_BLE_KEY_TYPE_ID");
            p_locak_keys = (tBTM_BLE_LOCAL_KEYS *)&btm_cb.devcb.id_keys;
            break;

        case BTM_BLE_KEY_TYPE_ER:
            BTM_TRACE_DEBUG ("BTM_BLE_KEY_TYPE_ER");
            p_locak_keys = (tBTM_BLE_LOCAL_KEYS *)&btm_cb.devcb.ble_encryption_key_value;
            break;

        default:
            BTM_TRACE_ERROR("unknown key type: %d", key_type);
            break;
        }
        if (p_locak_keys != NULL) {
            (*btm_cb.api.p_le_key_callback) (key_type, p_locak_keys);
        }
    }
}