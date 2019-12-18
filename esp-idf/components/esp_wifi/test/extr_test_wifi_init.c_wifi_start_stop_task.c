#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wifi_init_config_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  SemaphoreHandle_t ;

/* Variables and functions */
 char* EMPH_STR (char*) ; 
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (scalar_t__) ; 
 int /*<<< orphan*/  WIFI_INIT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  esp_netif_init () ; 
 scalar_t__ esp_wifi_deinit () ; 
 scalar_t__ esp_wifi_init (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_wifi_start () ; 
 scalar_t__ esp_wifi_stop () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  nvs_flash_deinit () ; 
 scalar_t__ nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 
 int /*<<< orphan*/  unity_reset_leak_checks () ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wifi_start_stop_task(void* arg)
{
    SemaphoreHandle_t *sema = (SemaphoreHandle_t *) arg;
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    //init nvs
    ESP_LOGI(TAG, EMPH_STR("nvs_flash_init"));
    esp_err_t r = nvs_flash_init();
    if (r == ESP_ERR_NVS_NO_FREE_PAGES || r == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	    ESP_LOGI(TAG, EMPH_STR("no free pages or NFS version mismatch, erase.."));
	    TEST_ESP_OK(nvs_flash_erase());
	    r = nvs_flash_init();
    }
    TEST_ESP_OK(r);
    //init tcpip stack
    ESP_LOGI(TAG, EMPH_STR("esp_netif_init"));
    esp_netif_init();
    //init event loop
    ESP_LOGI(TAG, EMPH_STR("event_init"));
    event_init();
    unity_reset_leak_checks();
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_init"));
    TEST_ASSERT(esp_wifi_init(&cfg) == ESP_OK);
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_start"));
    TEST_ASSERT(esp_wifi_start() == ESP_OK);
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_stop"));
    TEST_ASSERT(esp_wifi_stop() == ESP_OK);
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_stop"));
    TEST_ASSERT(esp_wifi_stop() == ESP_OK);
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_deinit"));
    TEST_ASSERT(esp_wifi_deinit() == ESP_OK);
    ESP_LOGI(TAG, EMPH_STR("nvs_flash_deinit..."));
    nvs_flash_deinit();
    ESP_LOGI(TAG, "test passed...");
    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}