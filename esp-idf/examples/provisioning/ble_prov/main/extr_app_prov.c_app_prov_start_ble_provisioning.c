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
struct app_prov_data {int security; int /*<<< orphan*/  timer; int /*<<< orphan*/  const* pop; } ;
typedef  int /*<<< orphan*/  protocomm_security_pop_t ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  dispatch_method; int /*<<< orphan*/ * arg; int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ esp_timer_create_args_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_EVENT_ANY_ID ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_TIMER_TASK ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  IP_EVENT_STA_GOT_IP ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  _stop_prov_cb ; 
 int /*<<< orphan*/  app_prov_event_handler ; 
 scalar_t__ app_prov_start_service () ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ esp_event_handler_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_timer_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct app_prov_data* g_prov ; 

esp_err_t app_prov_start_ble_provisioning(int security, const protocomm_security_pop_t *pop)
{
    /* If provisioning app data present,
     * means provisioning app is already running */
    if (g_prov) {
        ESP_LOGI(TAG, "Invalid provisioning state");
        return ESP_FAIL;
    }

    /* Allocate memory for provisioning app data */
    g_prov = (struct app_prov_data *) calloc(1, sizeof(struct app_prov_data));
    if (!g_prov) {
        ESP_LOGI(TAG, "Unable to allocate prov data");
        return ESP_ERR_NO_MEM;
    }

    /* Initialize app data */
    g_prov->pop = pop;
    g_prov->security = security;

    /* Create timer object as a member of app data */
    esp_timer_create_args_t timer_conf = {
        .callback = _stop_prov_cb,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "stop_ble_tm"
    };
    esp_err_t err = esp_timer_create(&timer_conf, &g_prov->timer);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create timer");
        return err;
    }

    err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, app_prov_event_handler, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register WiFi event handler");
        return err;
    }

    err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, app_prov_event_handler, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register IP event handler");
        return err;
    }

    /* Start provisioning service through BLE */
    err = app_prov_start_service();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Provisioning failed to start");
        return err;
    }

    ESP_LOGI(TAG, "BLE Provisioning started");
    return ESP_OK;
}