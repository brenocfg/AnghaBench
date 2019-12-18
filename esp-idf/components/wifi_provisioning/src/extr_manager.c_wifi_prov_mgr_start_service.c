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
struct TYPE_5__ {scalar_t__ (* set_config_service ) (int /*<<< orphan*/ ,char const*,char const*) ;scalar_t__ (* prov_start ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* prov_stop ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ wifi_prov_scheme_t ;
typedef  int /*<<< orphan*/  wifi_prov_scan_handlers_t ;
typedef  int /*<<< orphan*/  wifi_prov_config_handlers_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  cJSON ;
struct TYPE_4__ {TYPE_2__ scheme; } ;
struct TYPE_6__ {int security; char* wifi_prov_handlers; char* wifi_scan_handlers; int /*<<< orphan*/ * pc; int /*<<< orphan*/  pop; int /*<<< orphan*/  prov_scheme_config; TYPE_1__ mgr_config; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_EVENT_ANY_ID ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  IP_EVENT_STA_GOT_IP ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  cJSON_Delete (int /*<<< orphan*/ *) ; 
 char* cJSON_Print (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_event_handler_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_wifi_prov_handlers (char*) ; 
 scalar_t__ get_wifi_scan_handlers (char*) ; 
 void* malloc (int) ; 
 scalar_t__ protocomm_add_endpoint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  protocomm_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * protocomm_new () ; 
 int /*<<< orphan*/  protocomm_security0 ; 
 int /*<<< orphan*/  protocomm_security1 ; 
 scalar_t__ protocomm_set_security (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ protocomm_set_version (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_3__* prov_ctx ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wifi_prov_config_data_handler ; 
 int /*<<< orphan*/ * wifi_prov_get_info_json () ; 
 int /*<<< orphan*/  wifi_prov_mgr_event_handler_internal ; 
 int /*<<< orphan*/  wifi_prov_scan_handler ; 

__attribute__((used)) static esp_err_t wifi_prov_mgr_start_service(const char *service_name, const char *service_key)
{
    const wifi_prov_scheme_t *scheme = &prov_ctx->mgr_config.scheme;
    esp_err_t ret;

    /* Create new protocomm instance */
    prov_ctx->pc = protocomm_new();
    if (prov_ctx->pc == NULL) {
        ESP_LOGE(TAG, "Failed to create new protocomm instance");
        return ESP_FAIL;
    }

    ret = scheme->set_config_service(prov_ctx->prov_scheme_config, service_name, service_key);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure service");
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    /* Start provisioning */
    ret = scheme->prov_start(prov_ctx->pc, prov_ctx->prov_scheme_config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start service");
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    /* Set version information / capabilities of provisioning service and application */
    cJSON *version_json = wifi_prov_get_info_json();
    char *version_str = cJSON_Print(version_json);
    ret = protocomm_set_version(prov_ctx->pc, "proto-ver", version_str);
    free(version_str);
    cJSON_Delete(version_json);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set version endpoint");
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    /* Set protocomm security type for endpoint */
    if (prov_ctx->security == 0) {
        ret = protocomm_set_security(prov_ctx->pc, "prov-session",
                                     &protocomm_security0, NULL);
    } else if (prov_ctx->security == 1) {
        ret = protocomm_set_security(prov_ctx->pc, "prov-session",
                                     &protocomm_security1, &prov_ctx->pop);
    } else {
        ESP_LOGE(TAG, "Unsupported protocomm security version %d", prov_ctx->security);
        ret = ESP_ERR_INVALID_ARG;
    }
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set security endpoint");
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    prov_ctx->wifi_prov_handlers = malloc(sizeof(wifi_prov_config_handlers_t));
    ret = get_wifi_prov_handlers(prov_ctx->wifi_prov_handlers);
    if (ret != ESP_OK) {
        ESP_LOGD(TAG, "Failed to allocate memory for provisioning handlers");
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ESP_ERR_NO_MEM;
    }

    /* Add protocomm endpoint for Wi-Fi station configuration */
    ret = protocomm_add_endpoint(prov_ctx->pc, "prov-config",
                                 wifi_prov_config_data_handler,
                                 prov_ctx->wifi_prov_handlers);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set provisioning endpoint");
        free(prov_ctx->wifi_prov_handlers);
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    prov_ctx->wifi_scan_handlers = malloc(sizeof(wifi_prov_scan_handlers_t));
    ret = get_wifi_scan_handlers(prov_ctx->wifi_scan_handlers);
    if (ret != ESP_OK) {
        ESP_LOGD(TAG, "Failed to allocate memory for Wi-Fi scan handlers");
        free(prov_ctx->wifi_prov_handlers);
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ESP_ERR_NO_MEM;
    }

    /* Add endpoint for scanning Wi-Fi APs and sending scan list */
    ret = protocomm_add_endpoint(prov_ctx->pc, "prov-scan",
                                 wifi_prov_scan_handler,
                                 prov_ctx->wifi_scan_handlers);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set Wi-Fi scan endpoint");
        free(prov_ctx->wifi_scan_handlers);
        free(prov_ctx->wifi_prov_handlers);
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    /* Register global event handler */
    ret = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                     wifi_prov_mgr_event_handler_internal, NULL);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register WiFi event handler");
        free(prov_ctx->wifi_scan_handlers);
        free(prov_ctx->wifi_prov_handlers);
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    ret = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                     wifi_prov_mgr_event_handler_internal, NULL);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register IP event handler");
        esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                     wifi_prov_mgr_event_handler_internal);
        free(prov_ctx->wifi_scan_handlers);
        free(prov_ctx->wifi_prov_handlers);
        scheme->prov_stop(prov_ctx->pc);
        protocomm_delete(prov_ctx->pc);
        return ret;
    }

    ESP_LOGI(TAG, "Provisioning started with service name : %s ",
             service_name ? service_name : "<NULL>");
    return ESP_OK;
}