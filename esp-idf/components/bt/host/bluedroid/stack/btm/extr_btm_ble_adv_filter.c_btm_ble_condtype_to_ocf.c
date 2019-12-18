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
typedef  int UINT8 ;

/* Variables and functions */
 int BTM_BLE_META_PF_ADDR ; 
 int BTM_BLE_META_PF_ALL ; 
 int BTM_BLE_META_PF_LOCAL_NAME ; 
 int BTM_BLE_META_PF_MANU_DATA ; 
 int BTM_BLE_META_PF_SOL_UUID ; 
 int BTM_BLE_META_PF_SRVC_DATA ; 
 int BTM_BLE_META_PF_UUID ; 
#define  BTM_BLE_PF_ADDR_FILTER 134 
#define  BTM_BLE_PF_LOCAL_NAME 133 
#define  BTM_BLE_PF_MANU_DATA 132 
#define  BTM_BLE_PF_SRVC_DATA_PATTERN 131 
#define  BTM_BLE_PF_SRVC_SOL_UUID 130 
#define  BTM_BLE_PF_SRVC_UUID 129 
#define  BTM_BLE_PF_TYPE_ALL 128 
 int BTM_BLE_PF_TYPE_MAX ; 

UINT8 btm_ble_condtype_to_ocf(UINT8 cond_type)
{
    UINT8 ocf = 0;

    switch (cond_type) {
    case BTM_BLE_PF_ADDR_FILTER:
        ocf = BTM_BLE_META_PF_ADDR;
        break;
    case BTM_BLE_PF_SRVC_UUID:
        ocf = BTM_BLE_META_PF_UUID;
        break;
    case BTM_BLE_PF_SRVC_SOL_UUID:
        ocf = BTM_BLE_META_PF_SOL_UUID;
        break;
    case BTM_BLE_PF_LOCAL_NAME:
        ocf = BTM_BLE_META_PF_LOCAL_NAME;
        break;
    case BTM_BLE_PF_MANU_DATA:
        ocf = BTM_BLE_META_PF_MANU_DATA;
        break;
    case BTM_BLE_PF_SRVC_DATA_PATTERN:
        ocf = BTM_BLE_META_PF_SRVC_DATA;
        break;
    case BTM_BLE_PF_TYPE_ALL:
        ocf = BTM_BLE_META_PF_ALL;
        break;
    default:
        ocf = BTM_BLE_PF_TYPE_MAX;
        break;
    }
    return ocf;
}