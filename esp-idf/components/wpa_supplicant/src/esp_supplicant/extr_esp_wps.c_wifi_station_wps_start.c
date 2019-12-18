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
struct wps_sm {int is_wps_scan; int /*<<< orphan*/  wps_timeout_timer; int /*<<< orphan*/  scan_cnt; int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPS_CALC_KEY_PRE_CALC ; 
#define  WPS_STATUS_DISABLE 129 
#define  WPS_STATUS_SCANNING 128 
 int /*<<< orphan*/  esp_wifi_set_wps_start_flag_internal (int) ; 
 int /*<<< orphan*/  ets_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wifi_wps_scan () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_build_public_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wps_get_status () ; 
 struct wps_sm* wps_sm_get () ; 

int wifi_station_wps_start(void)
{
    struct wps_sm *sm = wps_sm_get();

    if (!sm) {
        wpa_printf(MSG_ERROR, "WPS: wps not initial");
        return ESP_FAIL;
    }

    ets_timer_arm(&sm->wps_timeout_timer, 120000, 0); /* 120s total */

    switch (wps_get_status()) {
    case WPS_STATUS_DISABLE: {
        sm->is_wps_scan = true;

        wps_build_public_key(sm->wps, NULL, WPS_CALC_KEY_PRE_CALC);

        wifi_wps_scan();


        break;
    }
    case WPS_STATUS_SCANNING:
        sm->scan_cnt = 0;
        ets_timer_disarm(&sm->wps_timeout_timer);
        ets_timer_arm(&sm->wps_timeout_timer, 120000, 0); /* 120s total */
        break;
    default:
        break;
    }
    esp_wifi_set_wps_start_flag_internal(true);
    return ESP_OK;
}