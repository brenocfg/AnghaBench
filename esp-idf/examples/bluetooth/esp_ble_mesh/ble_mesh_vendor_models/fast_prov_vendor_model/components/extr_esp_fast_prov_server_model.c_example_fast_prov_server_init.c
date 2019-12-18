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
struct TYPE_4__ {int /*<<< orphan*/  gatt_proxy_enable_timer; int /*<<< orphan*/  disable_fast_prov_timer; TYPE_2__* model; } ;
typedef  TYPE_1__ example_fast_prov_server_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__ user_data; } ;
typedef  TYPE_2__ esp_ble_mesh_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  disable_fast_prov_cb ; 
 int /*<<< orphan*/  enable_gatt_proxy_cb ; 
 int /*<<< orphan*/  k_delayed_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t example_fast_prov_server_init(esp_ble_mesh_model_t *model)
{
    example_fast_prov_server_t *srv = NULL;

    if (!model || !model->user_data) {
        return ESP_ERR_INVALID_ARG;
    }

    srv = (example_fast_prov_server_t *)model->user_data;
    srv->model = model;

    k_delayed_work_init(&srv->disable_fast_prov_timer, disable_fast_prov_cb);
    k_delayed_work_init(&srv->gatt_proxy_enable_timer, enable_gatt_proxy_cb);

    return ESP_OK;
}