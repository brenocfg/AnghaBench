#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int reason; } ;
typedef  TYPE_1__ wifi_event_sta_disconnected_t ;
typedef  scalar_t__ esp_event_base_t ;
struct TYPE_4__ {void* wifi_state; int /*<<< orphan*/  wifi_disconnect_reason; scalar_t__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IP_EVENT ; 
 int IP_EVENT_STA_GOT_IP ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WIFI_EVENT ; 
 int WIFI_EVENT_STA_DISCONNECTED ; 
 int WIFI_EVENT_STA_START ; 
 int /*<<< orphan*/  WIFI_PROV_STA_AP_NOT_FOUND ; 
 int /*<<< orphan*/  WIFI_PROV_STA_AUTH_ERROR ; 
 void* WIFI_PROV_STA_CONNECTED ; 
 void* WIFI_PROV_STA_CONNECTING ; 
 void* WIFI_PROV_STA_DISCONNECTED ; 
#define  WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT 134 
#define  WIFI_REASON_ASSOC_FAIL 133 
#define  WIFI_REASON_AUTH_EXPIRE 132 
#define  WIFI_REASON_AUTH_FAIL 131 
#define  WIFI_REASON_BEACON_TIMEOUT 130 
#define  WIFI_REASON_HANDSHAKE_TIMEOUT 129 
#define  WIFI_REASON_NO_AP_FOUND 128 
 int /*<<< orphan*/  esp_timer_start_once (scalar_t__,int) ; 
 int /*<<< orphan*/  esp_wifi_connect () ; 
 TYPE_2__* g_prov ; 

__attribute__((used)) static void app_prov_event_handler(void* handler_arg, esp_event_base_t event_base,
                                   int event_id, void* event_data)
{
    /* If pointer to provisioning application data is NULL
     * then provisioning is not running */
    if (!g_prov) {
        return;
    }

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "STA Start");
        /* Once configuration is received through protocomm,
         * device is started as station. Once station starts,
         * wait for connection to establish with configured
         * host SSID and password */
        g_prov->wifi_state = WIFI_PROV_STA_CONNECTING;
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ESP_LOGI(TAG, "STA Got IP");
        /* Station got IP. That means configuration is successful.
         * Schedule timer to stop provisioning app after 30 seconds. */
        g_prov->wifi_state = WIFI_PROV_STA_CONNECTED;
        if (g_prov && g_prov->timer) {
            esp_timer_start_once(g_prov->timer, 30000*1000U);
        }
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGE(TAG, "STA Disconnected");
        /* Station couldn't connect to configured host SSID */
        g_prov->wifi_state = WIFI_PROV_STA_DISCONNECTED;

        wifi_event_sta_disconnected_t* disconnected = (wifi_event_sta_disconnected_t*) event_data;
        ESP_LOGE(TAG, "Disconnect reason : %d", disconnected->reason);

        /* Set code corresponding to the reason for disconnection */
        switch (disconnected->reason) {
        case WIFI_REASON_AUTH_EXPIRE:
        case WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
        case WIFI_REASON_BEACON_TIMEOUT:
        case WIFI_REASON_AUTH_FAIL:
        case WIFI_REASON_ASSOC_FAIL:
        case WIFI_REASON_HANDSHAKE_TIMEOUT:
            ESP_LOGI(TAG, "STA Auth Error");
            g_prov->wifi_disconnect_reason = WIFI_PROV_STA_AUTH_ERROR;
            break;
        case WIFI_REASON_NO_AP_FOUND:
            ESP_LOGI(TAG, "STA AP Not found");
            g_prov->wifi_disconnect_reason = WIFI_PROV_STA_AP_NOT_FOUND;
            break;
        default:
            /* If none of the expected reasons,
             * retry connecting to host SSID */
            g_prov->wifi_state = WIFI_PROV_STA_CONNECTING;
            esp_wifi_connect();
        }
    }
}