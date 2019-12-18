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
struct TYPE_8__ {int nvs_enable; } ;
typedef  TYPE_2__ wifi_init_config_t ;
struct TYPE_7__ {int channel; int ssid_hidden; int max_connection; int beacon_interval; int /*<<< orphan*/  authmode; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
struct TYPE_9__ {TYPE_1__ ap; } ;
typedef  TYPE_3__ wifi_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PWD ; 
 int /*<<< orphan*/  DEFAULT_SSID ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_AUTH_WPA2_PSK ; 
 int /*<<< orphan*/  WIFI_IF_AP ; 
 TYPE_2__ WIFI_INIT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  WIFI_MODE_AP ; 
 int /*<<< orphan*/  esp_wifi_init (TYPE_2__*) ; 
 int /*<<< orphan*/  esp_wifi_set_config (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  esp_wifi_set_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_start () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  unity_reset_leak_checks () ; 
 int /*<<< orphan*/ * wifi_events ; 
 int /*<<< orphan*/ * xEventGroupCreate () ; 

__attribute__((used)) static void start_wifi_as_softap(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    cfg.nvs_enable = false;

    wifi_config_t w_config = {
        .ap.ssid = DEFAULT_SSID,
        .ap.password = DEFAULT_PWD,
        .ap.ssid_len = 0,
        .ap.channel = 1,
        .ap.authmode = WIFI_AUTH_WPA2_PSK,
        .ap.ssid_hidden = false,
        .ap.max_connection = 4,
        .ap.beacon_interval = 100,
    };

    event_init();

    // can't deinit event loop, need to reset leak check
    unity_reset_leak_checks();

    if (wifi_events == NULL) {
        wifi_events = xEventGroupCreate();
    }

    TEST_ESP_OK(esp_wifi_init(&cfg));
    TEST_ESP_OK(esp_wifi_set_mode(WIFI_MODE_AP));
    TEST_ESP_OK(esp_wifi_set_config(WIFI_IF_AP, &w_config));
    TEST_ESP_OK(esp_wifi_start());
}