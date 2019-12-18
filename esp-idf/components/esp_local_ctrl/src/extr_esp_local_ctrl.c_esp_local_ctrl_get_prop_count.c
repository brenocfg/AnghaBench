#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {size_t props_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* local_ctrl_inst_ctx ; 

esp_err_t esp_local_ctrl_get_prop_count(size_t *count)
{
    if (!local_ctrl_inst_ctx) {
        ESP_LOGE(TAG, "Service not running");
        return ESP_ERR_INVALID_STATE;
    }
    if (!count) {
        return ESP_ERR_INVALID_ARG;
    }
    *count = local_ctrl_inst_ctx->props_count;
    return ESP_OK;
}