#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_11__ {scalar_t__ tot_scan_results_strg; } ;
typedef  TYPE_2__ tBTM_BLE_VSC_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_TRACK_ADV_CBACK ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_track_adv_cback ) (TYPE_4__*) ;scalar_t__ ref_value; } ;
struct TYPE_12__ {TYPE_1__ ble_track_advert; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;
struct TYPE_13__ {scalar_t__ client_if; int /*<<< orphan*/  advertiser_info_present; } ;
typedef  TYPE_4__ tBTA_DM_BLE_TRACK_ADV_DATA ;
typedef  scalar_t__ UINT8 ;
typedef  TYPE_4__ BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_2__*) ; 
 scalar_t__ BTM_BleTrackAdvertiser (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  NO_ADV_INFO_PRESENT ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void bta_dm_ble_track_advertiser(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS btm_status = 0;
    BD_ADDR bda;
    memset(&bda, 0 , sizeof(BD_ADDR));
    tBTM_BLE_VSC_CB cmn_ble_vsc_cb;
    tBTA_DM_BLE_TRACK_ADV_DATA track_adv_data;

    BTM_BleGetVendorCapabilities(&cmn_ble_vsc_cb);

    if (0 != cmn_ble_vsc_cb.tot_scan_results_strg) {
        btm_status = BTM_BleTrackAdvertiser((tBTM_BLE_TRACK_ADV_CBACK *)
                                            p_data->ble_track_advert.p_track_adv_cback,
                                            p_data->ble_track_advert.ref_value);
    }

    if (BTM_CMD_STARTED != btm_status) {
        memset(&track_adv_data, 0, sizeof(tBTA_DM_BLE_TRACK_ADV_DATA));
        track_adv_data.advertiser_info_present = NO_ADV_INFO_PRESENT; /* Indicates failure */
        track_adv_data.client_if = (UINT8)p_data->ble_track_advert.ref_value;
        p_data->ble_track_advert.p_track_adv_cback(&track_adv_data);
    }
}