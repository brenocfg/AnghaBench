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
typedef  int /*<<< orphan*/  wifi_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPH_STR (char*) ; 
 int /*<<< orphan*/  ESP_ERR_WIFI_NOT_INIT ; 
 int /*<<< orphan*/  ESP_IF_WIFI_STA ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ESP_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_MODE_STA ; 
 int /*<<< orphan*/  esp_wifi_deinit () ; 
 int /*<<< orphan*/  esp_wifi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_wifi_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_wifi_set_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_start () ; 
 int /*<<< orphan*/  esp_wifi_stop () ; 

__attribute__((used)) static void test_wifi_start_stop(wifi_init_config_t *cfg, wifi_config_t* wifi_config)
{
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_stop"));
    TEST_ESP_ERR(ESP_ERR_WIFI_NOT_INIT, esp_wifi_stop());
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_init"));
    TEST_ESP_OK(esp_wifi_init(cfg));
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_set_mode"));
    TEST_ESP_OK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_set_config"));
    TEST_ESP_OK(esp_wifi_set_config(ESP_IF_WIFI_STA, wifi_config));
    //now start wifi
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_start..."));
    TEST_ESP_OK(esp_wifi_start());
    //wifi stop
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_stop..."));
    TEST_ESP_OK( esp_wifi_stop() );
    ESP_LOGI(TAG, EMPH_STR("esp_wifi_deinit..."));
    TEST_ESP_OK(esp_wifi_deinit());
}