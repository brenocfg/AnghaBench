#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  no_auto_stop; } ;
struct TYPE_5__ {TYPE_1__ capabilities; } ;
struct TYPE_6__ {TYPE_2__ mgr_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_3__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 
 int /*<<< orphan*/  wifi_prov_mgr_stop_provisioning () ; 

esp_err_t wifi_prov_mgr_done(void)
{
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    bool auto_stop_enabled = false;
    ACQUIRE_LOCK(prov_ctx_lock);
    if (prov_ctx && !prov_ctx->mgr_info.capabilities.no_auto_stop) {
        auto_stop_enabled = true;
    }
    RELEASE_LOCK(prov_ctx_lock);

    /* Stop provisioning if auto stop is enabled */
    if (auto_stop_enabled) {
        wifi_prov_mgr_stop_provisioning();
    }
    return ESP_OK;
}