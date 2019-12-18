#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_8__ {scalar_t__ filter_support; } ;
typedef  TYPE_2__ tBTM_BLE_VSC_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_FILT_INDEX ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_COND_PARAM ;
typedef  int /*<<< orphan*/  tBTA_STATUS ;
struct TYPE_7__ {int /*<<< orphan*/  ref_value; int /*<<< orphan*/  cond_type; int /*<<< orphan*/  (* p_filt_cfg_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ p_cond_param; scalar_t__ filt_index; int /*<<< orphan*/  action; } ;
struct TYPE_9__ {TYPE_1__ ble_cfg_filter_cond; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_scan_filt_cfg_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTA_DM_BLE_PF_CONFIG_EVT ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  BTM_BleCfgFilterCondition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_2__*) ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  bta_ble_scan_cfg_cmpl ; 
 TYPE_5__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_cfg_filter_cond (tBTA_DM_MSG *p_data)
{
    tBTM_STATUS st = BTM_MODE_UNSUPPORTED;
    tBTA_STATUS status = BTA_FAILURE;

    tBTM_BLE_VSC_CB cmn_vsc_cb;

    APPL_TRACE_DEBUG("bta_dm_cfg_filter_cond");
    BTM_BleGetVendorCapabilities(&cmn_vsc_cb);
    if (0 != cmn_vsc_cb.filter_support) {
        if ((st = BTM_BleCfgFilterCondition(p_data->ble_cfg_filter_cond.action,
                                            p_data->ble_cfg_filter_cond.cond_type,
                                            (tBTM_BLE_PF_FILT_INDEX)p_data->ble_cfg_filter_cond.filt_index,
                                            (tBTM_BLE_PF_COND_PARAM *)p_data->ble_cfg_filter_cond.p_cond_param,
                                            bta_ble_scan_cfg_cmpl, p_data->ble_cfg_filter_cond.ref_value))
                == BTM_CMD_STARTED) {
            bta_dm_cb.p_scan_filt_cfg_cback = p_data->ble_cfg_filter_cond.p_filt_cfg_cback;
            return;
        }
    }

    if (p_data->ble_cfg_filter_cond.p_filt_cfg_cback) {
        p_data->ble_cfg_filter_cond.p_filt_cfg_cback(BTA_DM_BLE_PF_CONFIG_EVT,
                p_data->ble_cfg_filter_cond.cond_type, 0, status,
                p_data->ble_cfg_filter_cond.ref_value);
    }
    return;
}