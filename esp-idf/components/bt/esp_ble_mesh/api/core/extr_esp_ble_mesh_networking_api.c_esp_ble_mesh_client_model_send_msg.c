#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_msg_ctx_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_dev_role_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_MESH_ACT_CLIENT_MODEL_SEND ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ble_mesh_model_send_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

esp_err_t esp_ble_mesh_client_model_send_msg(esp_ble_mesh_model_t *model,
        esp_ble_mesh_msg_ctx_t *ctx, uint32_t opcode,
        uint16_t length, uint8_t *data, int32_t msg_timeout,
        bool need_rsp, esp_ble_mesh_dev_role_t device_role)
{
    if (!model || !ctx) {
        return ESP_ERR_INVALID_ARG;
    }
    return ble_mesh_model_send_msg(model, ctx, opcode, BTC_BLE_MESH_ACT_CLIENT_MODEL_SEND,
                                   length, data, msg_timeout, need_rsp, device_role);
}