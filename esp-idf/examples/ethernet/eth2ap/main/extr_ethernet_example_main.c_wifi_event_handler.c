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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_IF_WIFI_AP ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
#define  WIFI_EVENT_AP_STACONNECTED 129 
#define  WIFI_EVENT_AP_STADISCONNECTED 128 
 int /*<<< orphan*/  esp_wifi_internal_reg_rxcb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pkt_wifi2eth ; 
 int s_sta_is_connected ; 

__attribute__((used)) static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    switch (event_id) {
    case WIFI_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "Wi-Fi AP got a station connected");
        s_sta_is_connected = true;
        esp_wifi_internal_reg_rxcb(ESP_IF_WIFI_AP, pkt_wifi2eth);
        break;
    case WIFI_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "Wi-Fi AP got a station disconnected");
        s_sta_is_connected = false;
        esp_wifi_internal_reg_rxcb(ESP_IF_WIFI_AP, NULL);
        break;
    default:
        break;
    }
}