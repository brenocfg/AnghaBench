#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  esp_gatts_cb_event_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  handle; int /*<<< orphan*/  len; int /*<<< orphan*/  value; scalar_t__ is_prep; } ;
struct TYPE_7__ {TYPE_1__ write; } ;
typedef  TYPE_2__ esp_ble_gatts_cb_param_t ;
struct TYPE_8__ {int /*<<< orphan*/  pc_ble; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_ble_gatts_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_ble_gatts_send_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_ble_gatts_set_attr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_to_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_write_event_env (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_4__* protoble_internal ; 
 scalar_t__ protocomm_req_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void transport_simple_ble_write(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    uint8_t *outbuf = NULL;
    ssize_t outlen = 0;
    esp_err_t ret;

    ESP_LOGD(TAG, "Inside write with session - %d on attr handle = %d \nlen = %d, is_prep = %d",
             param->write.conn_id, param->write.handle, param->write.len, param->write.is_prep);

    if (param->write.is_prep) {
        ret = prepare_write_event_env(gatts_if, param);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Error appending to prepare buffer");
        }
        return;
    } else {
        ESP_LOGD(TAG, "is_prep not set");
    }

    ret = protocomm_req_handle(protoble_internal->pc_ble,
                               handle_to_handler(param->write.handle),
                               param->write.conn_id,
                               param->write.value,
                               param->write.len,
                               &outbuf, &outlen);
    if (ret == ESP_OK) {
        ret = esp_ble_gatts_set_attr_value(param->write.handle, outlen, outbuf);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set the session attribute value");
        }
        ret = esp_ble_gatts_send_response(gatts_if, param->write.conn_id,
                                          param->write.trans_id, ESP_GATT_OK, NULL);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Send response error in write");
        }
        hexdump("Response from  write", outbuf, outlen);

    } else {
        ESP_LOGE(TAG, "Invalid content received, killing connection");
        esp_ble_gatts_close(gatts_if, param->write.conn_id);
    }
    if (outbuf) {
        free(outbuf);
    }
}