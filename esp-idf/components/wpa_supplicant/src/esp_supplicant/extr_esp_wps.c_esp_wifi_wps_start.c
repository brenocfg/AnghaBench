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
 int ESP_ERR_WIFI_STATE ; 
 int ESP_ERR_WIFI_WPS_SM ; 
 int ESP_ERR_WIFI_WPS_TYPE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SIG_PP_WPS ; 
 int /*<<< orphan*/  SIG_WPS_START ; 
 scalar_t__ WPS_STATUS_DISABLE ; 
 scalar_t__ WPS_STATUS_SCANNING ; 
 scalar_t__ WPS_TYPE_DISABLE ; 
 scalar_t__ esp_wifi_get_user_init_flag_internal () ; 
 int /*<<< orphan*/  ic_pp_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_wps_enabled ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_check_wifi_mode () ; 
 scalar_t__ wps_get_status () ; 
 scalar_t__ wps_get_type () ; 
 int /*<<< orphan*/  wps_post_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int esp_wifi_wps_start(int timeout_ms)
{
    if (ESP_OK != wps_check_wifi_mode()) {
        return ESP_ERR_WIFI_MODE;
    }

    API_MUTEX_TAKE();

    if (!s_wps_enabled) {
        wpa_printf(MSG_ERROR, "wps start: wps not enabled");
        API_MUTEX_GIVE();
        return ESP_ERR_WIFI_WPS_SM;
    }

    if (wps_get_type() == WPS_TYPE_DISABLE || (wps_get_status() != WPS_STATUS_DISABLE && wps_get_status() != WPS_STATUS_SCANNING)) {
        API_MUTEX_GIVE();
        return ESP_ERR_WIFI_WPS_TYPE;
    }

    if (esp_wifi_get_user_init_flag_internal() == 0) {
        API_MUTEX_GIVE();
        return ESP_ERR_WIFI_STATE;
    }

    wpa_printf(MSG_DEBUG, "wps scan");

#ifdef USE_WPS_TASK
    wps_post_block(SIG_WPS_START, 0);
#else
    ic_pp_post(SIG_PP_WPS, 0);
#endif

    API_MUTEX_GIVE();
    return ESP_OK;
}