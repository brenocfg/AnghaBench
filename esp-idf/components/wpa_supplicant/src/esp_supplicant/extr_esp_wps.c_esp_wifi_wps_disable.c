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

/* Variables and functions */
 int /*<<< orphan*/  API_MUTEX_GIVE () ; 
 int /*<<< orphan*/  API_MUTEX_TAKE () ; 
 int ESP_ERR_WIFI_MODE ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SIG_WPS_DISABLE ; 
 int /*<<< orphan*/  WPS_TYPE_DISABLE ; 
 int /*<<< orphan*/  esp_wifi_disconnect () ; 
 int /*<<< orphan*/  esp_wifi_set_wps_start_flag_internal (int) ; 
 int s_wps_enabled ; 
 int wifi_wps_disable_internal () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wps_check_wifi_mode () ; 
 int /*<<< orphan*/  wps_delete_timer () ; 
 int wps_post_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_set_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_task_deinit () ; 

int esp_wifi_wps_disable(void)
{
    int ret = 0;

    if (ESP_OK != wps_check_wifi_mode()) {
        return ESP_ERR_WIFI_MODE;
    }

    API_MUTEX_TAKE();

    if (!s_wps_enabled) {
        wpa_printf(MSG_DEBUG, "wps disable: already disabled");
        API_MUTEX_GIVE();
        return ESP_OK;
    }

    wpa_printf(MSG_INFO, "wifi_wps_disable\n");
    wps_set_type(WPS_TYPE_DISABLE); /* Notify WiFi task */

    /* Call wps_delete_timer to delete all WPS timer, no timer will call wps_post()
     * to post message to wps_task once this function returns.
     */
    wps_delete_timer();

#ifdef USE_WPS_TASK
    ret = wps_post_block(SIG_WPS_DISABLE, 0);
#else
    ret = wifi_wps_disable_internal();
#endif

    if (ESP_OK != ret) {
        wpa_printf(MSG_ERROR, "wps disable: failed to disable wps, ret=%d", ret);
    }

    esp_wifi_disconnect();
    esp_wifi_set_wps_start_flag_internal(false);
    wps_task_deinit();
    s_wps_enabled = false;
    API_MUTEX_GIVE();
    return ESP_OK;
}