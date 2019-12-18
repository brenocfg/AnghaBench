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
typedef  int /*<<< orphan*/  protocomm_console_config_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {int security; int /*<<< orphan*/ * pc; int /*<<< orphan*/ * pop; } ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  PROTOCOMM_CONSOLE_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* g_prov ; 
 scalar_t__ protocomm_add_endpoint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ protocomm_console_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocomm_console_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * protocomm_new () ; 
 int /*<<< orphan*/  protocomm_security0 ; 
 int /*<<< orphan*/  protocomm_security1 ; 
 int /*<<< orphan*/  protocomm_set_security (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocomm_set_version (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  wifi_prov_config_data_handler ; 
 int /*<<< orphan*/  wifi_prov_handlers ; 

__attribute__((used)) static esp_err_t app_prov_start_service(void)
{
    /* Create new protocomm instance */
    g_prov->pc = protocomm_new();
    if (g_prov->pc == NULL) {
        ESP_LOGE(TAG, "Failed to create new protocomm instance");
        return ESP_FAIL;
    }

    /* Config for protocomm_console_start() */
    protocomm_console_config_t config = PROTOCOMM_CONSOLE_DEFAULT_CONFIG();

    /* Start protocomm using console */
    if (protocomm_console_start(g_prov->pc, &config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start console provisioning");
        return ESP_FAIL;
    }

    /* Set protocomm version verification endpoint for protocol */
    protocomm_set_version(g_prov->pc, "proto-ver", "V0.1");

    /* Set protocomm security type for endpoint */
    if (g_prov->security == 0) {
        protocomm_set_security(g_prov->pc, "prov-session", &protocomm_security0, NULL);
    } else if (g_prov->security == 1) {
        protocomm_set_security(g_prov->pc, "prov-session", &protocomm_security1, g_prov->pop);
    }

    /* Add endpoint for provisioning to set wifi station config */
    if (protocomm_add_endpoint(g_prov->pc, "prov-config",
                               wifi_prov_config_data_handler,
                               (void *) &wifi_prov_handlers) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set provisioning endpoint");
        protocomm_console_stop(g_prov->pc);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Provisioning started");
    return ESP_OK;
}