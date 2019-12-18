#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  tk ;
typedef  int esp_gap_ble_cb_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_18__ {int /*<<< orphan*/  status; } ;
struct TYPE_17__ {scalar_t__ bd_addr; int /*<<< orphan*/  status; } ;
struct TYPE_15__ {int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  fail_reason; int /*<<< orphan*/  success; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  key_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  passkey; } ;
struct TYPE_12__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_16__ {TYPE_5__ auth_cmpl; TYPE_4__ ble_key; TYPE_3__ key_notif; TYPE_2__ ble_req; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_19__ {TYPE_8__ local_privacy_cmpl; TYPE_7__ remove_bond_dev_cmpl; TYPE_6__ ble_security; TYPE_1__ adv_start_cmpl; } ;
typedef  TYPE_9__ esp_ble_gap_cb_param_t ;
typedef  int* esp_bd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_CONFIG_FLAG ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT 141 
#define  ESP_GAP_BLE_ADV_START_COMPLETE_EVT 140 
#define  ESP_GAP_BLE_AUTH_CMPL_EVT 139 
#define  ESP_GAP_BLE_KEY_EVT 138 
#define  ESP_GAP_BLE_LOCAL_ER_EVT 137 
#define  ESP_GAP_BLE_LOCAL_IR_EVT 136 
#define  ESP_GAP_BLE_NC_REQ_EVT 135 
#define  ESP_GAP_BLE_OOB_REQ_EVT 134 
#define  ESP_GAP_BLE_PASSKEY_NOTIF_EVT 133 
#define  ESP_GAP_BLE_PASSKEY_REQ_EVT 132 
#define  ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT 131 
#define  ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT 130 
#define  ESP_GAP_BLE_SEC_REQ_EVT 129 
#define  ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT 128 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GATTS_TABLE_TAG ; 
 int /*<<< orphan*/  SCAN_RSP_CONFIG_FLAG ; 
 int /*<<< orphan*/  adv_config_done ; 
 int /*<<< orphan*/  esp_auth_req_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_confirm_reply (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_ble_gap_config_adv_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gap_security_rsp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_oob_req_reply (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  esp_key_type_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  heart_rate_adv_config ; 
 int /*<<< orphan*/  heart_rate_adv_params ; 
 int /*<<< orphan*/  heart_rate_scan_rsp_config ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  show_bonded_devices () ; 

__attribute__((used)) static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    ESP_LOGV(GATTS_TABLE_TAG, "GAP_EVT, event %d\n", event);

    switch (event) {
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&heart_rate_adv_params);
        }
        break;
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~ADV_CONFIG_FLAG);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&heart_rate_adv_params);
        }
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTS_TABLE_TAG, "advertising start failed, error status = %x", param->adv_start_cmpl.status);
            break;
        }
        ESP_LOGI(GATTS_TABLE_TAG, "advertising start success");
        break;
    case ESP_GAP_BLE_PASSKEY_REQ_EVT:                           /* passkey request event */
        ESP_LOGI(GATTS_TABLE_TAG, "ESP_GAP_BLE_PASSKEY_REQ_EVT");
        /* Call the following function to input the passkey which is displayed on the remote device */
        //esp_ble_passkey_reply(heart_rate_profile_tab[HEART_PROFILE_APP_IDX].remote_bda, true, 0x00);
        break;
    case ESP_GAP_BLE_OOB_REQ_EVT: {
        ESP_LOGI(GATTS_TABLE_TAG, "ESP_GAP_BLE_OOB_REQ_EVT");
        uint8_t tk[16] = {1}; //If you paired with OOB, both devices need to use the same tk
        esp_ble_oob_req_reply(param->ble_security.ble_req.bd_addr, tk, sizeof(tk));
        break;
    }
    case ESP_GAP_BLE_LOCAL_IR_EVT:                               /* BLE local IR event */
        ESP_LOGI(GATTS_TABLE_TAG, "ESP_GAP_BLE_LOCAL_IR_EVT");
        break;
    case ESP_GAP_BLE_LOCAL_ER_EVT:                               /* BLE local ER event */
        ESP_LOGI(GATTS_TABLE_TAG, "ESP_GAP_BLE_LOCAL_ER_EVT");
        break;
    case ESP_GAP_BLE_NC_REQ_EVT:
        /* The app will receive this evt when the IO has DisplayYesNO capability and the peer device IO also has DisplayYesNo capability.
        show the passkey number to the user to confirm it with the number displayed by peer device. */
        esp_ble_confirm_reply(param->ble_security.ble_req.bd_addr, true);
        ESP_LOGI(GATTS_TABLE_TAG, "ESP_GAP_BLE_NC_REQ_EVT, the passkey Notify number:%d", param->ble_security.key_notif.passkey);
        break;
    case ESP_GAP_BLE_SEC_REQ_EVT:
        /* send the positive(true) security response to the peer device to accept the security request.
        If not accept the security request, should send the security response with negative(false) accept value*/
        esp_ble_gap_security_rsp(param->ble_security.ble_req.bd_addr, true);
        break;
    case ESP_GAP_BLE_PASSKEY_NOTIF_EVT:  ///the app will receive this evt when the IO  has Output capability and the peer device IO has Input capability.
        ///show the passkey number to the user to input it in the peer device.
        ESP_LOGI(GATTS_TABLE_TAG, "The passkey Notify number:%06d", param->ble_security.key_notif.passkey);
        break;
    case ESP_GAP_BLE_KEY_EVT:
        //shows the ble key info share with peer device to the user.
        ESP_LOGI(GATTS_TABLE_TAG, "key type = %s", esp_key_type_to_str(param->ble_security.ble_key.key_type));
        break;
    case ESP_GAP_BLE_AUTH_CMPL_EVT: {
        esp_bd_addr_t bd_addr;
        memcpy(bd_addr, param->ble_security.auth_cmpl.bd_addr, sizeof(esp_bd_addr_t));
        ESP_LOGI(GATTS_TABLE_TAG, "remote BD_ADDR: %08x%04x",\
                (bd_addr[0] << 24) + (bd_addr[1] << 16) + (bd_addr[2] << 8) + bd_addr[3],
                (bd_addr[4] << 8) + bd_addr[5]);
        ESP_LOGI(GATTS_TABLE_TAG, "address type = %d", param->ble_security.auth_cmpl.addr_type);
        ESP_LOGI(GATTS_TABLE_TAG, "pair status = %s",param->ble_security.auth_cmpl.success ? "success" : "fail");
        if(!param->ble_security.auth_cmpl.success) {
            ESP_LOGI(GATTS_TABLE_TAG, "fail reason = 0x%x",param->ble_security.auth_cmpl.fail_reason);
        } else {
            ESP_LOGI(GATTS_TABLE_TAG, "auth mode = %s",esp_auth_req_to_str(param->ble_security.auth_cmpl.auth_mode));
        }
        show_bonded_devices();
        break;
    }
    case ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT: {
        ESP_LOGD(GATTS_TABLE_TAG, "ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT status = %d", param->remove_bond_dev_cmpl.status);
        ESP_LOGI(GATTS_TABLE_TAG, "ESP_GAP_BLE_REMOVE_BOND_DEV");
        ESP_LOGI(GATTS_TABLE_TAG, "-----ESP_GAP_BLE_REMOVE_BOND_DEV----");
        esp_log_buffer_hex(GATTS_TABLE_TAG, (void *)param->remove_bond_dev_cmpl.bd_addr, sizeof(esp_bd_addr_t));
        ESP_LOGI(GATTS_TABLE_TAG, "------------------------------------");
        break;
    }
    case ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT:
        if (param->local_privacy_cmpl.status != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTS_TABLE_TAG, "config local privacy failed, error status = %x", param->local_privacy_cmpl.status);
            break;
        }

        esp_err_t ret = esp_ble_gap_config_adv_data(&heart_rate_adv_config);
        if (ret){
            ESP_LOGE(GATTS_TABLE_TAG, "config adv data failed, error code = %x", ret);
        }else{
            adv_config_done |= ADV_CONFIG_FLAG;
        }

        ret = esp_ble_gap_config_adv_data(&heart_rate_scan_rsp_config);
        if (ret){
            ESP_LOGE(GATTS_TABLE_TAG, "config adv data failed, error code = %x", ret);
        }else{
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
        }

        break;
    default:
        break;
    }
}