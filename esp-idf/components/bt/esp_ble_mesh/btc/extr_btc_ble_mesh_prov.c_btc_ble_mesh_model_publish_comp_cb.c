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
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_4__ {int err_code; int /*<<< orphan*/ * model; } ;
struct TYPE_5__ {TYPE_1__ model_publish_comp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ esp_ble_mesh_model_cb_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_PUBLISH_COMP_EVT ; 
 int /*<<< orphan*/  btc_ble_mesh_model_callback (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_ble_mesh_model_publish_comp_cb(esp_ble_mesh_model_t *model, int err)
{
    esp_ble_mesh_model_cb_param_t mesh_param = {0};

    mesh_param.model_publish_comp.err_code = err;
    mesh_param.model_publish_comp.model = model;

    btc_ble_mesh_model_callback(&mesh_param, ESP_BLE_MESH_MODEL_PUBLISH_COMP_EVT);
    return;
}