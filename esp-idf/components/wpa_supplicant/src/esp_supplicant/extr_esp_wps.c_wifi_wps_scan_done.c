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
typedef  int /*<<< orphan*/  wifi_sta_config_t ;
struct TYPE_3__ {int /*<<< orphan*/  sta; } ;
typedef  TYPE_1__ wifi_config_t ;
struct wps_sm {int discover_ssid_cnt; scalar_t__ scan_cnt; int ignore_sel_reg; int /*<<< orphan*/  wps_scan_timer; int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP ; 
 scalar_t__ WPS_IGNORE_SEL_REG_MAX_CNT ; 
 scalar_t__ WPS_STATUS_DISABLE ; 
 scalar_t__ WPS_STATUS_PENDING ; 
 scalar_t__ WPS_STATUS_SCANNING ; 
 scalar_t__ WPS_TYPE_DISABLE ; 
 int /*<<< orphan*/  esp_event_send_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_connect () ; 
 int /*<<< orphan*/  esp_wifi_disconnect () ; 
 int /*<<< orphan*/  esp_wifi_set_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ets_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wps_get_status () ; 
 scalar_t__ wps_get_type () ; 
 int /*<<< orphan*/  wps_set_status (scalar_t__) ; 

void
wifi_wps_scan_done(void *arg, STATUS status)
{
    struct wps_sm *sm = gWpsSm;
    wifi_config_t wifi_config;

    if (wps_get_type() == WPS_TYPE_DISABLE) {
        return;
    }

    if (!sm) {
        return;
    }

    if (sm->discover_ssid_cnt == 1) {
        wps_set_status(WPS_STATUS_PENDING);
    } else if (sm->discover_ssid_cnt == 0)  {
        wps_set_status(WPS_STATUS_SCANNING);
    } else {
        wpa_printf(MSG_INFO, "PBC session overlap!");
        wps_set_status(WPS_STATUS_DISABLE);
        esp_event_send_internal(WIFI_EVENT, WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP, 0, 0, portMAX_DELAY);
    }

    wpa_printf(MSG_DEBUG, "wps scan_done discover_ssid_cnt = %d", sm->discover_ssid_cnt);

    sm->discover_ssid_cnt = 0;

    if (wps_get_status() == WPS_STATUS_PENDING) {
        esp_wifi_disconnect();

        memcpy(&wifi_config.sta, &sm->config, sizeof(wifi_sta_config_t));
        esp_wifi_set_config(0, &wifi_config);

        wpa_printf(MSG_DEBUG, "WPS: neg start");
        esp_wifi_connect();
    } else if (wps_get_status() == WPS_STATUS_SCANNING) {
        if (sm->scan_cnt < WPS_IGNORE_SEL_REG_MAX_CNT) {
            sm->ignore_sel_reg = true;
        }
        ets_timer_arm(&sm->wps_scan_timer, 100, 0);
    } else {
        return;
    }
}