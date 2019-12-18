#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  tk ;
typedef  int esp_gap_ble_cb_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
struct TYPE_12__ {char* fail_reason; int /*<<< orphan*/  success; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_11__ {char* passkey; } ;
struct TYPE_10__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_13__ {TYPE_4__ auth_cmpl; TYPE_3__ key_notif; TYPE_2__ ble_req; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
struct TYPE_15__ {TYPE_6__ local_privacy_cmpl; TYPE_5__ ble_security; TYPE_1__ adv_start_cmpl; } ;
typedef  TYPE_7__ esp_ble_gap_cb_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_CONFIG_FLAG ; 
 int /*<<< orphan*/  BLE_ANCS_TAG ; 
 int /*<<< orphan*/  ESP_BD_ADDR_LEN ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT 137 
#define  ESP_GAP_BLE_ADV_START_COMPLETE_EVT 136 
#define  ESP_GAP_BLE_AUTH_CMPL_EVT 135 
#define  ESP_GAP_BLE_NC_REQ_EVT 134 
#define  ESP_GAP_BLE_OOB_REQ_EVT 133 
#define  ESP_GAP_BLE_PASSKEY_NOTIF_EVT 132 
#define  ESP_GAP_BLE_PASSKEY_REQ_EVT 131 
#define  ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT 130 
#define  ESP_GAP_BLE_SEC_REQ_EVT 129 
#define  ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SCAN_RSP_CONFIG_FLAG ; 
 int /*<<< orphan*/  adv_config ; 
 int /*<<< orphan*/  adv_config_done ; 
 int /*<<< orphan*/  adv_params ; 
 int /*<<< orphan*/  esp_ble_confirm_reply (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_ble_gap_config_adv_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gap_security_rsp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_oob_req_reply (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_rsp_config ; 

__attribute__((used)) static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    ESP_LOGV(BLE_ANCS_TAG, "GAP_EVT, event %d\n", event);

    switch (event) {
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
        if (adv_config_done == 0) {
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~ADV_CONFIG_FLAG);
        if (adv_config_done == 0) {
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(BLE_ANCS_TAG, "advertising start failed, error status = %x", param->adv_start_cmpl.status);
            break;
        }
        ESP_LOGI(BLE_ANCS_TAG, "advertising start success");
        break;
    case ESP_GAP_BLE_PASSKEY_REQ_EVT:                           /* passkey request event */
        ESP_LOGI(BLE_ANCS_TAG, "ESP_GAP_BLE_PASSKEY_REQ_EVT");
        /* Call the following function to input the passkey which is displayed on the remote device */
        //esp_ble_passkey_reply(heart_rate_profile_tab[HEART_PROFILE_APP_IDX].remote_bda, true, 0x00);
        break;
    case ESP_GAP_BLE_OOB_REQ_EVT: {
        ESP_LOGI(BLE_ANCS_TAG, "ESP_GAP_BLE_OOB_REQ_EVT");
        uint8_t tk[16] = {1}; //If you paired with OOB, both devices need to use the same tk
        esp_ble_oob_req_reply(param->ble_security.ble_req.bd_addr, tk, sizeof(tk));
        break;
    }
    case ESP_GAP_BLE_NC_REQ_EVT:
        /* The app will receive this evt when the IO has DisplayYesNO capability and the peer device IO also has DisplayYesNo capability.
        show the passkey number to the user to confirm it with the number displayed by peer device. */
        esp_ble_confirm_reply(param->ble_security.ble_req.bd_addr, true);
        ESP_LOGI(BLE_ANCS_TAG, "ESP_GAP_BLE_NC_REQ_EVT, the passkey Notify number:%d", param->ble_security.key_notif.passkey);
        break;
    case ESP_GAP_BLE_SEC_REQ_EVT:
        /* send the positive(true) security response to the peer device to accept the security request.
        If not accept the security request, should send the security response with negative(false) accept value*/
        esp_ble_gap_security_rsp(param->ble_security.ble_req.bd_addr, true);
        break;
    case ESP_GAP_BLE_PASSKEY_NOTIF_EVT:  ///the app will receive this evt when the IO  has Output capability and the peer device IO has Input capability.
        ///show the passkey number to the user to input it in the peer device.
        ESP_LOGI(BLE_ANCS_TAG, "The passkey Notify number:%06d", param->ble_security.key_notif.passkey);
        break;
    case ESP_GAP_BLE_AUTH_CMPL_EVT: {
        esp_log_buffer_hex("addr", param->ble_security.auth_cmpl.bd_addr, ESP_BD_ADDR_LEN);
        ESP_LOGI(BLE_ANCS_TAG, "pair status = %s",param->ble_security.auth_cmpl.success ? "success" : "fail");
        if (!param->ble_security.auth_cmpl.success) {
            ESP_LOGI(BLE_ANCS_TAG, "fail reason = 0x%x",param->ble_security.auth_cmpl.fail_reason);
        }
        break;
    }
    case ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT:
        if (param->local_privacy_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(BLE_ANCS_TAG, "config local privacy failed, error status = %x", param->local_privacy_cmpl.status);
            break;
        }

        esp_err_t ret = esp_ble_gap_config_adv_data(&adv_config);
        if (ret) {
            ESP_LOGE(BLE_ANCS_TAG, "config adv data failed, error code = %x", ret);
        } else {
            adv_config_done |= ADV_CONFIG_FLAG;
        }

        ret = esp_ble_gap_config_adv_data(&scan_rsp_config);
        if (ret) {
            ESP_LOGE(BLE_ANCS_TAG, "config adv data failed, error code = %x", ret);
        } else {
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
        }

        break;
    default:
        break;
    }
}