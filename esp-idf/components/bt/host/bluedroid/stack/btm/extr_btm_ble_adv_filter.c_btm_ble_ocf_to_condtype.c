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
#define  BTM_BLE_META_PF_ADDR 135 
#define  BTM_BLE_META_PF_ALL 134 
#define  BTM_BLE_META_PF_FEAT_SEL 133 
#define  BTM_BLE_META_PF_LOCAL_NAME 132 
#define  BTM_BLE_META_PF_MANU_DATA 131 
#define  BTM_BLE_META_PF_SOL_UUID 130 
#define  BTM_BLE_META_PF_SRVC_DATA 129 
#define  BTM_BLE_META_PF_UUID 128 
 int BTM_BLE_PF_ADDR_FILTER ; 
 int BTM_BLE_PF_LOCAL_NAME ; 
 int BTM_BLE_PF_MANU_DATA ; 
 int BTM_BLE_PF_SRVC_DATA_PATTERN ; 
 int BTM_BLE_PF_SRVC_SOL_UUID ; 
 int BTM_BLE_PF_SRVC_UUID ; 
 int BTM_BLE_PF_TYPE_ALL ; 
 int BTM_BLE_PF_TYPE_MAX ; 

UINT8 btm_ble_ocf_to_condtype(UINT8 ocf)
{
    UINT8 cond_type = 0;

    switch (ocf) {
    case BTM_BLE_META_PF_FEAT_SEL:
        cond_type = BTM_BLE_META_PF_FEAT_SEL;
        break;
    case BTM_BLE_META_PF_ADDR:
        cond_type = BTM_BLE_PF_ADDR_FILTER;
        break;
    case BTM_BLE_META_PF_UUID:
        cond_type = BTM_BLE_PF_SRVC_UUID;
        break;
    case BTM_BLE_META_PF_SOL_UUID:
        cond_type = BTM_BLE_PF_SRVC_SOL_UUID;
        break;
    case BTM_BLE_META_PF_LOCAL_NAME:
        cond_type = BTM_BLE_PF_LOCAL_NAME;
        break;
    case BTM_BLE_META_PF_MANU_DATA:
        cond_type = BTM_BLE_PF_MANU_DATA;
        break;
    case BTM_BLE_META_PF_SRVC_DATA:
        cond_type = BTM_BLE_PF_SRVC_DATA_PATTERN;
        break;
    case BTM_BLE_META_PF_ALL:
        cond_type = BTM_BLE_PF_TYPE_ALL;
        break;
    default:
        cond_type = BTM_BLE_PF_TYPE_MAX;
        break;
    }
    return cond_type;
}