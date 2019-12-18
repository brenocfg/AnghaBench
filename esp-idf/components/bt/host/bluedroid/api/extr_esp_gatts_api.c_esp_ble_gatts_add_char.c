#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  esp_gatt_perm_t ;
typedef  int /*<<< orphan*/  esp_gatt_char_prop_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  esp_bt_uuid_t ;
struct TYPE_18__ {int /*<<< orphan*/  attr_value; int /*<<< orphan*/  attr_len; int /*<<< orphan*/  attr_max_len; } ;
typedef  TYPE_4__ esp_attr_value_t ;
struct TYPE_19__ {int /*<<< orphan*/  auto_rsp; } ;
typedef  TYPE_5__ esp_attr_control_t ;
struct TYPE_20__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_6__ btc_msg_t ;
struct TYPE_16__ {int /*<<< orphan*/  auto_rsp; } ;
struct TYPE_15__ {int /*<<< orphan*/  attr_value; int /*<<< orphan*/  attr_len; int /*<<< orphan*/  attr_max_len; } ;
struct TYPE_17__ {int /*<<< orphan*/  char_uuid; TYPE_2__ attr_control; TYPE_1__ char_val; int /*<<< orphan*/  property; int /*<<< orphan*/  perm; int /*<<< orphan*/  service_handle; } ;
struct TYPE_21__ {TYPE_3__ add_char; } ;
typedef  TYPE_7__ btc_ble_gatts_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GATTS_ACT_ADD_CHAR ; 
 int /*<<< orphan*/  BTC_PID_GATTS ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_ENABLED ; 
 scalar_t__ ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  btc_gatts_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_6__*,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_ble_gatts_add_char_desc_param_check (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_ble_gatts_add_char(uint16_t service_handle,  esp_bt_uuid_t  *char_uuid,
                                 esp_gatt_perm_t perm, esp_gatt_char_prop_t property, esp_attr_value_t *char_val,
                                 esp_attr_control_t *control)
{
    btc_msg_t msg;
    btc_ble_gatts_args_t arg;
    esp_err_t status;

    ESP_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    /* parameter validation check */
    status = esp_ble_gatts_add_char_desc_param_check(char_val, control);
    if (status != ESP_OK){
        return status;
    }

    memset(&arg, 0, sizeof(btc_ble_gatts_args_t));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTS;
    msg.act = BTC_GATTS_ACT_ADD_CHAR;
    arg.add_char.service_handle = service_handle;
    arg.add_char.perm = perm;
    arg.add_char.property = property;
    if (char_val != NULL) {
        arg.add_char.char_val.attr_max_len = char_val->attr_max_len;
        arg.add_char.char_val.attr_len = char_val->attr_len;
        arg.add_char.char_val.attr_value = char_val->attr_value;
    }

    if (control != NULL) {
        arg.add_char.attr_control.auto_rsp = control->auto_rsp;
    }
    memcpy(&arg.add_char.char_uuid, char_uuid, sizeof(esp_bt_uuid_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gatts_args_t), btc_gatts_arg_deep_copy) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}