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
typedef  int /*<<< orphan*/  system_event_id_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SYSTEM_EVENT_AP_PROBEREQRECVED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_AP_STACONNECTED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_AP_STADISCONNECTED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_AP_START ; 
 int /*<<< orphan*/  SYSTEM_EVENT_AP_STOP ; 
 int /*<<< orphan*/  SYSTEM_EVENT_MAX ; 
 int /*<<< orphan*/  SYSTEM_EVENT_SCAN_DONE ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_AUTHMODE_CHANGE ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_CONNECTED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_DISCONNECTED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_START ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_STOP ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_WPS_ER_FAILED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_WPS_ER_PIN ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_WPS_ER_SUCCESS ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_WPS_ER_TIMEOUT ; 
 int /*<<< orphan*/  SYSTEM_EVENT_WIFI_READY ; 
 int /*<<< orphan*/  TAG ; 
#define  WIFI_EVENT_AP_PROBEREQRECVED 144 
#define  WIFI_EVENT_AP_STACONNECTED 143 
#define  WIFI_EVENT_AP_STADISCONNECTED 142 
#define  WIFI_EVENT_AP_START 141 
#define  WIFI_EVENT_AP_STOP 140 
#define  WIFI_EVENT_SCAN_DONE 139 
#define  WIFI_EVENT_STA_AUTHMODE_CHANGE 138 
#define  WIFI_EVENT_STA_CONNECTED 137 
#define  WIFI_EVENT_STA_DISCONNECTED 136 
#define  WIFI_EVENT_STA_START 135 
#define  WIFI_EVENT_STA_STOP 134 
#define  WIFI_EVENT_STA_WPS_ER_FAILED 133 
#define  WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP 132 
#define  WIFI_EVENT_STA_WPS_ER_PIN 131 
#define  WIFI_EVENT_STA_WPS_ER_SUCCESS 130 
#define  WIFI_EVENT_STA_WPS_ER_TIMEOUT 129 
#define  WIFI_EVENT_WIFI_READY 128 

__attribute__((used)) static system_event_id_t esp_event_legacy_wifi_event_id(int32_t event_id)
{
    switch (event_id) {
    case WIFI_EVENT_WIFI_READY:
        return SYSTEM_EVENT_WIFI_READY;

    case WIFI_EVENT_SCAN_DONE:
        return SYSTEM_EVENT_SCAN_DONE;

    case WIFI_EVENT_STA_START:
        return SYSTEM_EVENT_STA_START;

    case WIFI_EVENT_STA_STOP:
        return SYSTEM_EVENT_STA_STOP;

    case WIFI_EVENT_STA_CONNECTED:
        return SYSTEM_EVENT_STA_CONNECTED;

    case WIFI_EVENT_STA_DISCONNECTED:
        return SYSTEM_EVENT_STA_DISCONNECTED;

    case WIFI_EVENT_STA_AUTHMODE_CHANGE:
        return SYSTEM_EVENT_STA_AUTHMODE_CHANGE;

    case WIFI_EVENT_STA_WPS_ER_SUCCESS:
        return SYSTEM_EVENT_STA_WPS_ER_SUCCESS;

    case WIFI_EVENT_STA_WPS_ER_FAILED:
        return SYSTEM_EVENT_STA_WPS_ER_FAILED;

    case WIFI_EVENT_STA_WPS_ER_TIMEOUT:
        return SYSTEM_EVENT_STA_WPS_ER_TIMEOUT;

    case WIFI_EVENT_STA_WPS_ER_PIN:
        return SYSTEM_EVENT_STA_WPS_ER_PIN;

    case WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP:
        return SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP;

    case WIFI_EVENT_AP_START:
        return SYSTEM_EVENT_AP_START;

    case WIFI_EVENT_AP_STOP:
        return SYSTEM_EVENT_AP_STOP;

    case WIFI_EVENT_AP_STACONNECTED:
        return SYSTEM_EVENT_AP_STACONNECTED;

    case WIFI_EVENT_AP_STADISCONNECTED:
        return SYSTEM_EVENT_AP_STADISCONNECTED;

    case WIFI_EVENT_AP_PROBEREQRECVED:
        return SYSTEM_EVENT_AP_PROBEREQRECVED;

    default:
        ESP_LOGE(TAG, "invalid wifi event id %d", event_id);
        return SYSTEM_EVENT_MAX;
    }
}