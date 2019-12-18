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
typedef  int /*<<< orphan*/  cJSON ;
struct TYPE_2__ {scalar_t__ prov_state; int /*<<< orphan*/ * app_info_json; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WIFI_PROV_STATE_IDLE ; 
 int /*<<< orphan*/  cJSON_AddItemToArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cJSON_AddItemToObject (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cJSON_AddStringToObject (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * cJSON_CreateArray () ; 
 void* cJSON_CreateObject () ; 
 int /*<<< orphan*/  cJSON_CreateString (char const*) ; 
 TYPE_1__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

esp_err_t wifi_prov_mgr_set_app_info(const char *label, const char *version,
                                     const char**capabilities, size_t total_capabilities)
{
    if (!label || !version || !capabilities) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = ESP_FAIL;
    ACQUIRE_LOCK(prov_ctx_lock);

    if (prov_ctx && prov_ctx->prov_state == WIFI_PROV_STATE_IDLE) {
        if (!prov_ctx->app_info_json) {
            prov_ctx->app_info_json = cJSON_CreateObject();
        }

        cJSON *new_entry_json = cJSON_CreateObject();
        cJSON *capabilities_json = cJSON_CreateArray();
        cJSON_AddItemToObject(prov_ctx->app_info_json, label, new_entry_json);

        /* Version ("ver") */
        cJSON_AddStringToObject(new_entry_json, "ver", version);

        /* List of capabilities ("cap") */
        cJSON_AddItemToObject(new_entry_json, "cap", capabilities_json);
        for (unsigned int i = 0; i < total_capabilities; i++) {
            if (capabilities[i]) {
                cJSON_AddItemToArray(capabilities_json, cJSON_CreateString(capabilities[i]));
            }
        }
        ret = ESP_OK;
    } else {
        ret = ESP_ERR_INVALID_STATE;
    }

    RELEASE_LOCK(prov_ctx_lock);
    return ret;
}