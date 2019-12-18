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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  btc_ble_mesh_client_model_init (int /*<<< orphan*/ *) ; 

esp_err_t esp_ble_mesh_client_model_init(esp_ble_mesh_model_t *model)
{
    if (model == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return btc_ble_mesh_client_model_init(model);
}