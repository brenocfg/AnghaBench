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
struct TYPE_4__ {int bssid_set; int /*<<< orphan*/  bssid; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {TYPE_1__ sta; } ;
typedef  TYPE_2__ wifi_config_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ EventBits_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PWD ; 
 int /*<<< orphan*/  DEFAULT_SSID ; 
 scalar_t__ GOT_IP_EVENT ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_IF_STA ; 
 int /*<<< orphan*/  esp_wifi_connect () ; 
 int /*<<< orphan*/  esp_wifi_set_config (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  wifi_events ; 
 scalar_t__ xEventGroupWaitBits (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wifi_connect_by_bssid(uint8_t *bssid)
{
    EventBits_t bits;

    wifi_config_t w_config = {
        .sta.ssid = DEFAULT_SSID,
        .sta.password = DEFAULT_PWD,
        .sta.bssid_set = true,
    };

    memcpy(w_config.sta.bssid, bssid, 6);

    TEST_ESP_OK(esp_wifi_set_config(WIFI_IF_STA, &w_config));
    TEST_ESP_OK(esp_wifi_connect());
    bits = xEventGroupWaitBits(wifi_events, GOT_IP_EVENT, 1, 0, 5000/portTICK_RATE_MS);
    TEST_ASSERT(bits == GOT_IP_EVENT);
}