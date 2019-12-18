#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void** p_flags; void** p_pad; void** ad_data; int /*<<< orphan*/  data_mask; } ;
typedef  TYPE_3__ tBTM_BLE_LOCAL_ADV_DATA ;
typedef  void* UINT8 ;
struct TYPE_5__ {TYPE_3__ adv_data; } ;
struct TYPE_6__ {TYPE_1__ inq_var; } ;
struct TYPE_8__ {TYPE_2__ ble_ctr_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_AD_BIT_FLAGS ; 
 int BTM_BLE_AD_DATA_LEN ; 
 int /*<<< orphan*/  BTM_BLE_AD_TYPE_FLAG ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,void*) ; 
 TYPE_4__ btm_cb ; 
 scalar_t__ btsnd_hcic_ble_set_adv_data (void*,void**) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btm_ble_update_adv_flag(UINT8 flag)
{
    tBTM_BLE_LOCAL_ADV_DATA *p_adv_data = &btm_cb.ble_ctr_cb.inq_var.adv_data;
    UINT8   *p;

    BTM_TRACE_DEBUG ("btm_ble_update_adv_flag new=0x%x", flag);

    if (p_adv_data->p_flags != NULL) {
        BTM_TRACE_DEBUG ("btm_ble_update_adv_flag old=0x%x",   *p_adv_data->p_flags);
        *p_adv_data->p_flags = flag;
    } else { /* no FLAGS in ADV data*/
        p = (p_adv_data->p_pad == NULL) ? p_adv_data->ad_data : p_adv_data->p_pad;
        /* need 3 bytes space to stuff in the flags, if not */
        /* erase all written data, just for flags */
        if ((BTM_BLE_AD_DATA_LEN - (p - p_adv_data->ad_data)) < 3) {
            p = p_adv_data->p_pad = p_adv_data->ad_data;
            memset(p_adv_data->ad_data, 0, BTM_BLE_AD_DATA_LEN);
        }

        *p++ = 2;
        *p++ = BTM_BLE_AD_TYPE_FLAG;
        p_adv_data->p_flags = p;
        *p++ = flag;
        p_adv_data->p_pad = p;
    }

    if (btsnd_hcic_ble_set_adv_data((UINT8)(p_adv_data->p_pad - p_adv_data->ad_data),
                                    p_adv_data->ad_data)) {
        p_adv_data->data_mask |= BTM_BLE_AD_BIT_FLAGS;
    }

}