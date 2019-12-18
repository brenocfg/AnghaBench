#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ password; scalar_t__ ssid; } ;
struct TYPE_5__ {TYPE_1__ sta; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ wifi_config_t ;

/* Variables and functions */
 int CONNECTED_BIT ; 
 int DISCONNECTED_BIT ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_IF_WIFI_STA ; 
 int /*<<< orphan*/  esp_wifi_connect () ; 
 int /*<<< orphan*/  esp_wifi_disconnect () ; 
 int /*<<< orphan*/  esp_wifi_set_config (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int portTICK_RATE_MS ; 
 int reconnect ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  wifi_event_group ; 
 int /*<<< orphan*/  xEventGroupClearBits (int /*<<< orphan*/ ,int) ; 
 int xEventGroupWaitBits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool wifi_cmd_sta_join(const char *ssid, const char *pass)
{
    int bits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, 0, 1, 0);

    wifi_config_t wifi_config = { 0 };

    strlcpy((char *) wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
    if (pass) {
        strncpy((char *) wifi_config.sta.password, pass, sizeof(wifi_config.sta.password));
    }

    if (bits & CONNECTED_BIT) {
        reconnect = false;
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        ESP_ERROR_CHECK( esp_wifi_disconnect() );
        xEventGroupWaitBits(wifi_event_group, DISCONNECTED_BIT, 0, 1, portTICK_RATE_MS);
    }

    reconnect = true;
    esp_wifi_disconnect();
    //ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) ); //by snake
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_connect() );

    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, 0, 1, 5000 / portTICK_RATE_MS);

    return true;
}