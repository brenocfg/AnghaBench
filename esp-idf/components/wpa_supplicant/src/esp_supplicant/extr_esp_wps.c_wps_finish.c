#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wifi_sta_config_t ;
struct TYPE_8__ {scalar_t__ bssid_set; int /*<<< orphan*/  bssid; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
struct TYPE_9__ {TYPE_2__ sta; } ;
typedef  TYPE_3__ wifi_config_t ;
struct wps_sm {int /*<<< orphan*/  wps_success_cb_timer; int /*<<< orphan*/  bssid; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  wps_msg_timeout_timer; int /*<<< orphan*/  wps_timeout_timer; TYPE_1__* wps; } ;
struct TYPE_7__ {scalar_t__ state; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_WPS_ER_FAILED ; 
 int /*<<< orphan*/  WPS_FAIL_REASON_NORMAL ; 
 scalar_t__ WPS_FINISHED ; 
 int /*<<< orphan*/  WPS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  esp_event_send_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_disarm_sta_connection_timer_internal () ; 
 int /*<<< orphan*/  esp_wifi_set_config (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ets_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_timer_disarm (int /*<<< orphan*/ *) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  os_free (TYPE_3__*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_set_status (int /*<<< orphan*/ ) ; 
 int wps_stop_process (int /*<<< orphan*/ ) ; 

int wps_finish(void)
{
    struct wps_sm *sm = gWpsSm;
    int ret = ESP_FAIL;

    if (!gWpsSm) {
        return ESP_FAIL;
    }

    if (sm->wps->state == WPS_FINISHED) {
        wifi_config_t *config = (wifi_config_t *)os_zalloc(sizeof(wifi_config_t));

        if (config == NULL) {
            esp_event_send_internal(WIFI_EVENT, WIFI_EVENT_STA_WPS_ER_FAILED, 0, 0, portMAX_DELAY);
            return ESP_FAIL;
        }

        wpa_printf(MSG_DEBUG, "wps finished------>");
        wps_set_status(WPS_STATUS_SUCCESS);
        esp_wifi_disarm_sta_connection_timer_internal();
        ets_timer_disarm(&sm->wps_timeout_timer);
        ets_timer_disarm(&sm->wps_msg_timeout_timer);

        memset(config, 0x00, sizeof(wifi_sta_config_t));
        memcpy(config->sta.ssid, sm->ssid, sm->ssid_len);
        memcpy(config->sta.password, sm->key, sm->key_len);
        memcpy(config->sta.bssid, sm->bssid, ETH_ALEN);
        config->sta.bssid_set = 0;
        esp_wifi_set_config(0, config);
        os_free(config);
        config = NULL;

        ets_timer_disarm(&sm->wps_success_cb_timer);
        ets_timer_arm(&sm->wps_success_cb_timer, 1000, 0);

        ret = 0;
    } else {
        wpa_printf(MSG_ERROR, "wps failed----->");

        ret = wps_stop_process(WPS_FAIL_REASON_NORMAL);
    }

    return ret;
}