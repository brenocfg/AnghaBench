#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wifi_mode_t ;
struct TYPE_7__ {int ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
typedef  TYPE_1__ wifi_event_sta_connected_t ;
struct TYPE_8__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  rssi; } ;
typedef  TYPE_2__ wifi_ap_record_t ;
typedef  int uint16_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;
typedef  TYPE_2__ esp_blufi_ap_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLUFI_ERROR (char*) ; 
 int /*<<< orphan*/  BLUFI_INFO (char*) ; 
 int /*<<< orphan*/  CONNECTED_BIT ; 
 int /*<<< orphan*/  ESP_BLUFI_STA_CONN_FAIL ; 
 int /*<<< orphan*/  ESP_BLUFI_STA_CONN_SUCCESS ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
#define  WIFI_EVENT_AP_START 132 
#define  WIFI_EVENT_SCAN_DONE 131 
#define  WIFI_EVENT_STA_CONNECTED 130 
#define  WIFI_EVENT_STA_DISCONNECTED 129 
#define  WIFI_EVENT_STA_START 128 
 int /*<<< orphan*/  esp_blufi_send_wifi_conn_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_blufi_send_wifi_list (int,TYPE_2__*) ; 
 int /*<<< orphan*/  esp_wifi_connect () ; 
 int /*<<< orphan*/  esp_wifi_get_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_wifi_scan_get_ap_num (int*) ; 
 int /*<<< orphan*/  esp_wifi_scan_get_ap_records (int*,TYPE_2__*) ; 
 int /*<<< orphan*/  esp_wifi_scan_stop () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_sta_bssid ; 
 int gl_sta_connected ; 
 int /*<<< orphan*/  gl_sta_ssid ; 
 int gl_sta_ssid_len ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wifi_event_group ; 
 int /*<<< orphan*/  xEventGroupClearBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    wifi_event_sta_connected_t *event;
    wifi_mode_t mode;

    switch (event_id) {
    case WIFI_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case WIFI_EVENT_STA_CONNECTED:
        gl_sta_connected = true;
        event = (wifi_event_sta_connected_t*) event_data;
        memcpy(gl_sta_bssid, event->bssid, 6);
        memcpy(gl_sta_ssid, event->ssid, event->ssid_len);
        gl_sta_ssid_len = event->ssid_len;
        break; 
    case WIFI_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        gl_sta_connected = false;
        memset(gl_sta_ssid, 0, 32);
        memset(gl_sta_bssid, 0, 6);
        gl_sta_ssid_len = 0;
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    case WIFI_EVENT_AP_START:
        esp_wifi_get_mode(&mode);

        /* TODO: get config or information of softap, then set to report extra_info */
        if (gl_sta_connected) {  
            esp_blufi_send_wifi_conn_report(mode, ESP_BLUFI_STA_CONN_SUCCESS, 0, NULL);
        } else {
            esp_blufi_send_wifi_conn_report(mode, ESP_BLUFI_STA_CONN_FAIL, 0, NULL);
        }
        break;
    case WIFI_EVENT_SCAN_DONE: {
        uint16_t apCount = 0;
        esp_wifi_scan_get_ap_num(&apCount);
        if (apCount == 0) {
            BLUFI_INFO("Nothing AP found");
            break;
        }
        wifi_ap_record_t *ap_list = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * apCount);
        if (!ap_list) {
            BLUFI_ERROR("malloc error, ap_list is NULL");
            break;
        }
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&apCount, ap_list));
        esp_blufi_ap_record_t * blufi_ap_list = (esp_blufi_ap_record_t *)malloc(apCount * sizeof(esp_blufi_ap_record_t));
        if (!blufi_ap_list) {
            if (ap_list) {
                free(ap_list);
            }
            BLUFI_ERROR("malloc error, blufi_ap_list is NULL");
            break;
        }
        for (int i = 0; i < apCount; ++i)
        {
            blufi_ap_list[i].rssi = ap_list[i].rssi;
            memcpy(blufi_ap_list[i].ssid, ap_list[i].ssid, sizeof(ap_list[i].ssid));
        }
        esp_blufi_send_wifi_list(apCount, blufi_ap_list);
        esp_wifi_scan_stop();
        free(ap_list);
        free(blufi_ap_list);
        break;
    }
    default:
        break;
    }
    return;
}