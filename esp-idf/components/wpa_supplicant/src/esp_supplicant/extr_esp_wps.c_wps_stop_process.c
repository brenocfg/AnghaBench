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
typedef  int /*<<< orphan*/  wifi_sta_config_t ;
typedef  int /*<<< orphan*/  wifi_event_sta_wps_fail_reason_t ;
typedef  int /*<<< orphan*/  u8 ;
struct wps_sm {int /*<<< orphan*/  wps_success_cb_timer; int /*<<< orphan*/  wps_msg_timeout_timer; int /*<<< orphan*/  config; scalar_t__ ssid_len; int /*<<< orphan*/ * ssid; int /*<<< orphan*/ * bssid; TYPE_1__* wps; scalar_t__ discover_ssid_cnt; scalar_t__ scan_cnt; } ;
typedef  int /*<<< orphan*/  reason_code ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int ESP_OK ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SEND_M1 ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_WPS_ER_FAILED ; 
 int /*<<< orphan*/  WPS_STATUS_DISABLE ; 
 int /*<<< orphan*/  esp_event_send_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_disarm_sta_connection_timer_internal () ; 
 int /*<<< orphan*/  esp_wifi_disconnect () ; 
 int /*<<< orphan*/  ets_timer_disarm (int /*<<< orphan*/ *) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  os_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_set_status (int /*<<< orphan*/ ) ; 

int wps_stop_process(wifi_event_sta_wps_fail_reason_t reason_code)
{
    struct wps_sm *sm = gWpsSm;

    if (!gWpsSm) {
        return ESP_FAIL;
    }

    wps_set_status(WPS_STATUS_DISABLE);
    sm->scan_cnt = 0;
    sm->discover_ssid_cnt = 0;
    sm->wps->state = SEND_M1;
    os_bzero(sm->bssid, ETH_ALEN);
    os_bzero(sm->ssid, 32);
    sm->ssid_len = 0;
    os_bzero((u8 *)&sm->config, sizeof(wifi_sta_config_t));

    esp_wifi_disarm_sta_connection_timer_internal();
    ets_timer_disarm(&sm->wps_msg_timeout_timer);
    ets_timer_disarm(&sm->wps_success_cb_timer);

    esp_wifi_disconnect();

    wpa_printf(MSG_DEBUG, "Write wps_fail_information");
    
    esp_event_send_internal(WIFI_EVENT, WIFI_EVENT_STA_WPS_ER_FAILED, &reason_code, sizeof(reason_code), portMAX_DELAY);

    return ESP_OK;
}