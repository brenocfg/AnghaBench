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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_IF_WIFI_AP ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ *) ; 
 char* MACSTR ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_get_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_wifi_as_softap () ; 
 int /*<<< orphan*/  stop_wifi () ; 
 int /*<<< orphan*/  test_case_uses_tcpip () ; 
 int /*<<< orphan*/  unity_send_signal_param (char*,char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void test_wifi_connection_softap(void)
{
    char mac_str[19] = {0};
    uint8_t mac[6];

    test_case_uses_tcpip();

    start_wifi_as_softap();

    TEST_ESP_OK(esp_wifi_get_mac(ESP_IF_WIFI_AP, mac));
    sprintf(mac_str, MACSTR, MAC2STR(mac));

    unity_send_signal_param("SoftAP mac", mac_str);

    unity_wait_for_signal("STA connected");

    vTaskDelay(60000 / portTICK_PERIOD_MS);

    stop_wifi();
}