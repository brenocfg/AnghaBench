#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_duplicate_info_t ;
typedef  scalar_t__ esp_ble_duplicate_exceptional_info_type_t ;
typedef  int /*<<< orphan*/  esp_bd_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {int /*<<< orphan*/  device_info; scalar_t__ info_type; int /*<<< orphan*/  subcode; } ;
struct TYPE_8__ {TYPE_1__ update_duplicate_exceptional_list; } ;
typedef  TYPE_3__ btc_ble_gap_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GAP_BLE_UPDATE_DUPLICATE_SCAN_EXCEPTIONAL_LIST ; 
 int /*<<< orphan*/  BTC_PID_GAP_BLE ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_ADD ; 
 scalar_t__ ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_LINK_ID ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_ble_gap_add_duplicate_scan_exceptional_device(esp_ble_duplicate_exceptional_info_type_t type, esp_duplicate_info_t device_info)
{
    btc_msg_t msg;
    btc_ble_gap_args_t arg;

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }
    if (!device_info && type <= ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_LINK_ID) {
        return ESP_ERR_INVALID_SIZE;
    }
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = BTC_GAP_BLE_UPDATE_DUPLICATE_SCAN_EXCEPTIONAL_LIST;
    arg.update_duplicate_exceptional_list.subcode = ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_ADD;
    arg.update_duplicate_exceptional_list.info_type = type;
    if (device_info) {
        memcpy(arg.update_duplicate_exceptional_list.device_info, device_info, sizeof(esp_bd_addr_t));
    }

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gap_args_t), NULL)
                == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}