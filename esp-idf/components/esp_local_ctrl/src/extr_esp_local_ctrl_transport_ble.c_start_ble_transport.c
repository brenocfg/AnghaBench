#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  protocomm_t ;
struct TYPE_3__ {int /*<<< orphan*/  ble; } ;
typedef  TYPE_1__ esp_local_ctrl_transport_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  protocomm_ble_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t start_ble_transport(protocomm_t *pc, const esp_local_ctrl_transport_config_t *config)
{
    if (!config || !config->ble) {
        ESP_LOGE(TAG, "NULL configuration provided");
        return ESP_ERR_INVALID_ARG;
    }
    return protocomm_ble_start(pc, config->ble);
}