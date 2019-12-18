#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
struct bt_mesh_model {int dummy; } ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_4__ {int /*<<< orphan*/  time; int /*<<< orphan*/ * model; } ;
struct TYPE_5__ {TYPE_1__ attention_on; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ esp_ble_mesh_health_server_cb_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_HEALTH_SERVER_ATTENTION_ON_EVT ; 
 int /*<<< orphan*/  btc_ble_mesh_health_server_callback (TYPE_2__*,int /*<<< orphan*/ ) ; 

void btc_ble_mesh_health_server_attention_on(struct bt_mesh_model *model, u8_t time)
{
    esp_ble_mesh_health_server_cb_param_t param = {0};

    param.attention_on.model = (esp_ble_mesh_model_t *)model;
    param.attention_on.time = time;

    btc_ble_mesh_health_server_callback(&param, ESP_BLE_MESH_HEALTH_SERVER_ATTENTION_ON_EVT);
}