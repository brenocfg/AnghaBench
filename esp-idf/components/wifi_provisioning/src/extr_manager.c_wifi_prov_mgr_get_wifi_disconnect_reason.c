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
typedef  int /*<<< orphan*/  wifi_prov_sta_fail_reason_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {scalar_t__ wifi_state; int /*<<< orphan*/  wifi_disconnect_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WIFI_PROV_STA_DISCONNECTED ; 
 TYPE_1__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

esp_err_t wifi_prov_mgr_get_wifi_disconnect_reason(wifi_prov_sta_fail_reason_t *reason)
{
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ACQUIRE_LOCK(prov_ctx_lock);
    if (prov_ctx == NULL || reason == NULL) {
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }

    if (prov_ctx->wifi_state != WIFI_PROV_STA_DISCONNECTED) {
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }

    *reason = prov_ctx->wifi_disconnect_reason;
    RELEASE_LOCK(prov_ctx_lock);
    return ESP_OK;
}