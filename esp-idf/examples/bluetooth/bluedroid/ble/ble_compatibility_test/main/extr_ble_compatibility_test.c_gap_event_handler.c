#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int esp_gap_ble_cb_event_t ;
struct TYPE_21__ {scalar_t__ bd_addr; int /*<<< orphan*/  status; } ;
struct TYPE_19__ {int /*<<< orphan*/  fail_reason; int /*<<< orphan*/  success; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  key_type; } ;
struct TYPE_17__ {int /*<<< orphan*/  passkey; } ;
struct TYPE_16__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_20__ {TYPE_7__ auth_cmpl; TYPE_6__ ble_key; TYPE_5__ key_notif; TYPE_4__ ble_req; } ;
struct TYPE_15__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  conn_int; int /*<<< orphan*/  max_int; int /*<<< orphan*/  min_int; int /*<<< orphan*/  status; } ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
struct TYPE_13__ {int /*<<< orphan*/  status; } ;
struct TYPE_12__ {TYPE_9__ remove_bond_dev_cmpl; TYPE_8__ ble_security; TYPE_3__ update_conn_params; TYPE_2__ adv_stop_cmpl; TYPE_1__ adv_start_cmpl; } ;
typedef  TYPE_10__ esp_ble_gap_cb_param_t ;
typedef  int* esp_bd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_CONFIG_FLAG ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT 141 
#define  ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT 140 
#define  ESP_GAP_BLE_ADV_START_COMPLETE_EVT 139 
#define  ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT 138 
#define  ESP_GAP_BLE_AUTH_CMPL_EVT 137 
#define  ESP_GAP_BLE_KEY_EVT 136 
#define  ESP_GAP_BLE_NC_REQ_EVT 135 
#define  ESP_GAP_BLE_PASSKEY_NOTIF_EVT 134 
#define  ESP_GAP_BLE_PASSKEY_REQ_EVT 133 
#define  ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT 132 
#define  ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT 131 
#define  ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT 130 
#define  ESP_GAP_BLE_SEC_REQ_EVT 129 
#define  ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EXAMPLE_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 int /*<<< orphan*/  SCAN_RSP_CONFIG_FLAG ; 
 int /*<<< orphan*/  adv_config_done ; 
 int /*<<< orphan*/  adv_params ; 
 int /*<<< orphan*/  esp_ble_gap_security_rsp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_key_type_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  show_bonded_devices () ; 

__attribute__((used)) static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    #ifdef CONFIG_SET_RAW_ADV_DATA
        case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
    #else
        case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
    #endif
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
            /* advertising start complete event to indicate advertising start successfully or failed */
            if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(EXAMPLE_TAG, "advertising start failed");
            }else{
                ESP_LOGI(EXAMPLE_TAG, "(0) ***** advertising start successfully ***** \n");
            }
            break;
        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(EXAMPLE_TAG, "Advertising stop failed");
            }
            else {
                ESP_LOGI(EXAMPLE_TAG, "Stop adv successfully\n");
            }
            break;
        case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
            EXAMPLE_DEBUG(EXAMPLE_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
            break;
        case ESP_GAP_BLE_PASSKEY_REQ_EVT:                           /* passkey request event */
            EXAMPLE_DEBUG(EXAMPLE_TAG, "ESP_GAP_BLE_PASSKEY_REQ_EVT");
            //esp_ble_passkey_reply(heart_rate_profile_tab[HEART_PROFILE_APP_IDX].remote_bda, true, 0x00);
            break;
        
        case ESP_GAP_BLE_NC_REQ_EVT:
            /* The app will receive this event when the IO has DisplayYesNO capability and the peer device IO also has DisplayYesNo capability.
            show the passkey number to the user to confirm it with the number displayed by peer device. */
            ESP_LOGI(EXAMPLE_TAG, "ESP_GAP_BLE_NC_REQ_EVT, the passkey Notify number:%d", param->ble_security.key_notif.passkey);
            break;
        case ESP_GAP_BLE_SEC_REQ_EVT:
            /* send the positive(true) security response to the peer device to accept the security request.
            If not accept the security request, should send the security response with negative(false) accept value*/
            esp_ble_gap_security_rsp(param->ble_security.ble_req.bd_addr, true);
            break;
        case ESP_GAP_BLE_PASSKEY_NOTIF_EVT:  ///the app will receive this evt when the IO has Output capability and the peer device IO has Input capability.
            ///show the passkey number to the user to input it in the peer device.
            ESP_LOGI(EXAMPLE_TAG, "The passkey notify number:%d", param->ble_security.key_notif.passkey);
            break;
        case ESP_GAP_BLE_KEY_EVT:
            //shows the ble key info share with peer device to the user.
            EXAMPLE_DEBUG(EXAMPLE_TAG, "key type = %s", esp_key_type_to_str(param->ble_security.ble_key.key_type));
            break;
        case ESP_GAP_BLE_AUTH_CMPL_EVT: {
            esp_bd_addr_t bd_addr;
            memcpy(bd_addr, param->ble_security.auth_cmpl.bd_addr, sizeof(esp_bd_addr_t));
            EXAMPLE_DEBUG(EXAMPLE_TAG, "remote BD_ADDR: %08x%04x",\
                    (bd_addr[0] << 24) + (bd_addr[1] << 16) + (bd_addr[2] << 8) + bd_addr[3],
                    (bd_addr[4] << 8) + bd_addr[5]);
            EXAMPLE_DEBUG(EXAMPLE_TAG, "address type = %d", param->ble_security.auth_cmpl.addr_type);
            if (param->ble_security.auth_cmpl.success){
                ESP_LOGI(EXAMPLE_TAG, "(1) ***** pair status = success ***** \n");
            }
            else {
                ESP_LOGI(EXAMPLE_TAG, "***** pair status = fail, reason = 0x%x *****\n", param->ble_security.auth_cmpl.fail_reason);
            }
            show_bonded_devices();
            break;
        }
        case ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT: {
            EXAMPLE_DEBUG(EXAMPLE_TAG, "ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT status = %d", param->remove_bond_dev_cmpl.status);
            #if DEBUG_ON
            esp_log_buffer_hex(EXAMPLE_TAG, (void *)param->remove_bond_dev_cmpl.bd_addr, sizeof(esp_bd_addr_t));
            #endif 
            EXAMPLE_DEBUG(EXAMPLE_TAG, "------------------------------------");
            break;
        }
        default:
            break;
    }
}