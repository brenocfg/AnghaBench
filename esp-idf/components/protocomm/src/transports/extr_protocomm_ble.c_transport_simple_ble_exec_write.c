#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  esp_gatts_cb_event_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_6__ {scalar_t__ exec_write_flag; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  conn_id; } ;
struct TYPE_7__ {TYPE_1__ exec_write; } ;
typedef  TYPE_2__ esp_ble_gatts_cb_param_t ;
struct TYPE_9__ {scalar_t__ prepare_len; int /*<<< orphan*/ * prepare_buf; int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  pc_ble; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_GATT_OK ; 
 scalar_t__ ESP_GATT_PREP_WRITE_EXEC ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_ble_gatts_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_ble_gatts_send_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gatts_set_attr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_to_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ prepare_write_env ; 
 TYPE_4__* protoble_internal ; 
 scalar_t__ protocomm_req_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void transport_simple_ble_exec_write(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    esp_err_t err;
    uint8_t *outbuf = NULL;
    ssize_t outlen = 0;
    ESP_LOGD(TAG, "Inside exec_write w/ session - %d", param->exec_write.conn_id);

    if ((param->exec_write.exec_write_flag == ESP_GATT_PREP_WRITE_EXEC)
            &&
            prepare_write_env.prepare_buf) {
        err = protocomm_req_handle(protoble_internal->pc_ble,
                                   handle_to_handler(prepare_write_env.handle),
                                   param->exec_write.conn_id,
                                   prepare_write_env.prepare_buf,
                                   prepare_write_env.prepare_len,
                                   &outbuf, &outlen);

        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Invalid content received, killing connection");
            esp_ble_gatts_close(gatts_if, param->exec_write.conn_id);
        } else {
            hexdump("Response from exec write", outbuf, outlen);
            esp_ble_gatts_set_attr_value(prepare_write_env.handle, outlen, outbuf);
        }
    }
    if (prepare_write_env.prepare_buf) {
        free(prepare_write_env.prepare_buf);
        prepare_write_env.prepare_buf = NULL;
        prepare_write_env.prepare_len = 0;
    }

    err = esp_ble_gatts_send_response(gatts_if, param->exec_write.conn_id, param->exec_write.trans_id, ESP_GATT_OK, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Send response error in exec write");
    }
    if (outbuf) {
        free(outbuf);
    }
}