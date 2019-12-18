#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nvs_enable; } ;
typedef  TYPE_1__ wifi_init_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_HANDLER_FLAG_DO_NOT_AUTO_RECONNECT ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 TYPE_1__ WIFI_INIT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  WIFI_MODE_STA ; 
 int /*<<< orphan*/  esp_wifi_init (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_wifi_set_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_start () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  unity_reset_leak_checks () ; 
 int /*<<< orphan*/  wifi_event_handler_flag ; 
 int /*<<< orphan*/ * wifi_events ; 
 int /*<<< orphan*/  xEventGroupClearBits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xEventGroupCreate () ; 

__attribute__((used)) static void start_wifi_as_sta(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    cfg.nvs_enable = false;

    // do not auto connect
    wifi_event_handler_flag |= EVENT_HANDLER_FLAG_DO_NOT_AUTO_RECONNECT;
    event_init();

    // can't deinit event loop, need to reset leak check
    unity_reset_leak_checks();

    if (wifi_events == NULL) {
        wifi_events = xEventGroupCreate();
    } else {
        xEventGroupClearBits(wifi_events, 0x00ffffff);
    }

    TEST_ESP_OK(esp_wifi_init(&cfg));
    TEST_ESP_OK(esp_wifi_set_mode(WIFI_MODE_STA));
    TEST_ESP_OK(esp_wifi_start());

}