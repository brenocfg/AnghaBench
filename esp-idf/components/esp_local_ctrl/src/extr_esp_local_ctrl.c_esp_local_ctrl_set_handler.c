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
typedef  int /*<<< orphan*/  protocomm_req_handler_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* local_ctrl_inst_ctx ; 
 scalar_t__ protocomm_add_endpoint (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*) ; 

esp_err_t esp_local_ctrl_set_handler(const char *ep_name,
                                     protocomm_req_handler_t handler,
                                     void *priv_data)
{
    esp_err_t ret = ESP_ERR_INVALID_STATE;

    if (local_ctrl_inst_ctx) {
        ret = protocomm_add_endpoint(local_ctrl_inst_ctx->pc, ep_name,
                                     handler, priv_data);
    }

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register endpoint handler");
    }
    return ret;
}