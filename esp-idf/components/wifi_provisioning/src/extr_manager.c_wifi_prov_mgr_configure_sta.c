#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sta; } ;
typedef  TYPE_3__ wifi_config_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  wifi_mode; } ;
struct TYPE_8__ {TYPE_1__ scheme; } ;
struct TYPE_10__ {scalar_t__ prov_state; int /*<<< orphan*/  wifi_state; TYPE_2__ mgr_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_IF_WIFI_STA ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WIFI_PROV_CRED_RECV ; 
 scalar_t__ WIFI_PROV_STATE_CRED_RECV ; 
 int /*<<< orphan*/  WIFI_PROV_STA_CONNECTING ; 
 int /*<<< orphan*/  WIFI_STORAGE_FLASH ; 
 int /*<<< orphan*/  debug_print_wifi_credentials (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ esp_wifi_connect () ; 
 scalar_t__ esp_wifi_set_config (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ esp_wifi_set_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_wifi_set_storage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_event_cb (int /*<<< orphan*/ ,void*,int) ; 
 int portTICK_PERIOD_MS ; 
 TYPE_5__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

esp_err_t wifi_prov_mgr_configure_sta(wifi_config_t *wifi_cfg)
{
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ACQUIRE_LOCK(prov_ctx_lock);
    if (!prov_ctx) {
        ESP_LOGE(TAG, "Invalid state of Provisioning app");
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }
    if (prov_ctx->prov_state >= WIFI_PROV_STATE_CRED_RECV) {
        ESP_LOGE(TAG, "Wi-Fi credentials already received by provisioning app");
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }
    debug_print_wifi_credentials(wifi_cfg->sta, "Received");

    /* Configure Wi-Fi as both AP and/or Station */
    if (esp_wifi_set_mode(prov_ctx->mgr_config.scheme.wifi_mode) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set Wi-Fi mode");
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }

    /* Don't release mutex yet as it is possible that right after
     * esp_wifi_connect()  is called below, the related Wi-Fi event
     * happens even before manager state is updated in the next
     * few lines causing the internal event handler to miss */

    /* Set Wi-Fi storage again to flash to keep the newly
     * provided credentials on NVS */
    if (esp_wifi_set_storage(WIFI_STORAGE_FLASH) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set storage Wi-Fi");
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }
    /* Configure Wi-Fi station with host credentials
     * provided during provisioning */
    if (esp_wifi_set_config(ESP_IF_WIFI_STA, wifi_cfg) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set Wi-Fi configuration");
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }
    /* Connect to AP */
    if (esp_wifi_connect() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to connect Wi-Fi");
        RELEASE_LOCK(prov_ctx_lock);
        return ESP_FAIL;
    }
    /* This delay allows channel change to complete */
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    /* Reset Wi-Fi station state for provisioning app */
    prov_ctx->wifi_state = WIFI_PROV_STA_CONNECTING;
    prov_ctx->prov_state = WIFI_PROV_STATE_CRED_RECV;
    /* Execute user registered callback handler */
    execute_event_cb(WIFI_PROV_CRED_RECV, (void *)&wifi_cfg->sta, sizeof(wifi_cfg->sta));
    RELEASE_LOCK(prov_ctx_lock);

    return ESP_OK;
}