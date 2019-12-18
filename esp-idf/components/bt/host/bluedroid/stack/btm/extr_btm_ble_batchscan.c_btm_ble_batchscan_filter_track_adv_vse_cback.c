#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ version_supported; } ;
typedef  TYPE_2__ tBTM_BLE_VSC_CB ;
struct TYPE_9__ {int /*<<< orphan*/  address; } ;
struct TYPE_11__ {scalar_t__ filt_index; scalar_t__ advertiser_state; scalar_t__ advertiser_info_present; scalar_t__ addr_type; scalar_t__ tx_power; scalar_t__ rssi_value; scalar_t__ adv_pkt_len; scalar_t__ scan_rsp_len; TYPE_1__ bd_addr; void* p_scan_rsp_data; void* p_adv_pkt_data; int /*<<< orphan*/  time_stamp; scalar_t__ client_if; } ;
typedef  TYPE_3__ tBTM_BLE_TRACK_ADV_DATA ;
typedef  scalar_t__ UINT8 ;
struct TYPE_13__ {int /*<<< orphan*/  (* p_track_cback ) (TYPE_3__*) ;scalar_t__ ref_value; } ;
struct TYPE_12__ {int /*<<< orphan*/  ref_value; int /*<<< orphan*/  (* p_thres_cback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ADV_INFO_PRESENT ; 
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_2__*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,scalar_t__,...) ; 
 scalar_t__ BTM_VSC_CHIP_CAPABILITY_L_VERSION ; 
 scalar_t__ HCI_VSE_SUBCODE_BLE_THRESHOLD_SUB_EVT ; 
 scalar_t__ HCI_VSE_SUBCODE_BLE_TRACKING_SUB_EVT ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 TYPE_7__ ble_advtrack_cb ; 
 TYPE_6__ ble_batchscan_cb ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* osi_malloc (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

void btm_ble_batchscan_filter_track_adv_vse_cback(UINT8 len, UINT8 *p)
{
    tBTM_BLE_TRACK_ADV_DATA adv_data;

    UINT8   sub_event = 0;
    tBTM_BLE_VSC_CB cmn_ble_vsc_cb;
    STREAM_TO_UINT8(sub_event, p);

    BTM_TRACE_EVENT("btm_ble_batchscan_filter_track_adv_vse_cback called with event:%x", sub_event);
    if (HCI_VSE_SUBCODE_BLE_THRESHOLD_SUB_EVT == sub_event &&
            NULL != ble_batchscan_cb.p_thres_cback) {
        ble_batchscan_cb.p_thres_cback(ble_batchscan_cb.ref_value);
        return;
    }

    if (HCI_VSE_SUBCODE_BLE_TRACKING_SUB_EVT == sub_event && NULL != ble_advtrack_cb.p_track_cback) {
        if (len < 10) {
            return;
        }

        memset(&adv_data, 0 , sizeof(tBTM_BLE_TRACK_ADV_DATA));
        BTM_BleGetVendorCapabilities(&cmn_ble_vsc_cb);
        adv_data.client_if = (UINT8)ble_advtrack_cb.ref_value;
        if (cmn_ble_vsc_cb.version_supported > BTM_VSC_CHIP_CAPABILITY_L_VERSION) {
            STREAM_TO_UINT8(adv_data.filt_index, p);
            STREAM_TO_UINT8(adv_data.advertiser_state, p);
            STREAM_TO_UINT8(adv_data.advertiser_info_present, p);
            STREAM_TO_BDADDR(adv_data.bd_addr.address, p);
            STREAM_TO_UINT8(adv_data.addr_type, p);

            /* Extract the adv info details */
            if (ADV_INFO_PRESENT == adv_data.advertiser_info_present) {
                STREAM_TO_UINT8(adv_data.tx_power, p);
                STREAM_TO_UINT8(adv_data.rssi_value, p);
                STREAM_TO_UINT16(adv_data.time_stamp, p);

                STREAM_TO_UINT8(adv_data.adv_pkt_len, p);
                if (adv_data.adv_pkt_len > 0) {
                    adv_data.p_adv_pkt_data = osi_malloc(adv_data.adv_pkt_len);
                    memcpy(adv_data.p_adv_pkt_data, p, adv_data.adv_pkt_len);
                }

                STREAM_TO_UINT8(adv_data.scan_rsp_len, p);
                if (adv_data.scan_rsp_len > 0) {
                    adv_data.p_scan_rsp_data = osi_malloc(adv_data.scan_rsp_len);
                    memcpy(adv_data.p_scan_rsp_data, p, adv_data.scan_rsp_len);
                }
            }
        } else {
            /* Based on L-release version */
            STREAM_TO_UINT8(adv_data.filt_index, p);
            STREAM_TO_UINT8(adv_data.addr_type, p);
            STREAM_TO_BDADDR(adv_data.bd_addr.address, p);
            STREAM_TO_UINT8(adv_data.advertiser_state, p);
        }

        BTM_TRACE_EVENT("track_adv_vse_cback called: %d, %d, %d", adv_data.filt_index,
                        adv_data.addr_type, adv_data.advertiser_state);
        ble_advtrack_cb.p_track_cback(&adv_data);
        return;
    }
}