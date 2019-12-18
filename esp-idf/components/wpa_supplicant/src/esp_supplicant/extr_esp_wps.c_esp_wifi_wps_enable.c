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
typedef  int /*<<< orphan*/  esp_wps_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_MUTEX_GIVE () ; 
 int /*<<< orphan*/  API_MUTEX_TAKE () ; 
 int ESP_ERR_WIFI_MODE ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SIG_WPS_ENABLE ; 
 int /*<<< orphan*/  WPS_TASK_STACK_SIZE ; 
 int s_wps_enabled ; 
 int wifi_wps_enable_internal (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wps_check_wifi_mode () ; 
 int wps_post_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_task_deinit () ; 
 int wps_task_init () ; 

int esp_wifi_wps_enable(const esp_wps_config_t *config)
{
    int ret;

    if (ESP_OK != wps_check_wifi_mode()) {
        return ESP_ERR_WIFI_MODE;
    }

    API_MUTEX_TAKE();
    if (s_wps_enabled) {
        API_MUTEX_GIVE();
        wpa_printf(MSG_DEBUG, "wps enable: already enabled");
        return ESP_OK;
    }

#ifdef USE_WPS_TASK
    ret = wps_task_init();
    if (ESP_OK != ret) {
        API_MUTEX_GIVE();
        return ret;
    }

    ret = wps_post_block(SIG_WPS_ENABLE, (esp_wps_config_t *)config);
    if (ESP_OK != ret) {
        wps_task_deinit();
        API_MUTEX_GIVE();
        return ret;
    }

    s_wps_enabled = true;
    wpa_printf(MSG_DEBUG, "wifi wps task: prio:%d, stack:%d\n", 2, WPS_TASK_STACK_SIZE);
    API_MUTEX_GIVE();
    return ret;
#else
    ret = wifi_wps_enable_internal(config);
    API_MUTEX_GIVE();
    return ret;
#endif
}