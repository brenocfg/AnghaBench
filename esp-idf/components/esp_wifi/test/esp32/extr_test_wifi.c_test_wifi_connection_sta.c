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
typedef  scalar_t__ EventBits_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECT_EVENT ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  start_wifi_as_sta () ; 
 int /*<<< orphan*/  stop_wifi () ; 
 int /*<<< orphan*/  test_case_uses_tcpip () ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_util_convert_mac_from_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unity_wait_for_signal_param (char*,char*,int) ; 
 int /*<<< orphan*/  wifi_connect_by_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wifi_events ; 
 scalar_t__ xEventGroupWaitBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_wifi_connection_sta(void)
{
    char mac_str[19];
    uint8_t mac[6];
    EventBits_t bits;

    test_case_uses_tcpip();

    start_wifi_as_sta();

    unity_wait_for_signal_param("SoftAP mac", mac_str, 19);

    TEST_ASSERT_TRUE(unity_util_convert_mac_from_string(mac_str, mac));

    wifi_connect_by_bssid(mac);

    unity_send_signal("STA connected");

    bits = xEventGroupWaitBits(wifi_events, DISCONNECT_EVENT, 1, 0, 60000 / portTICK_RATE_MS);
    // disconnect event not triggered
    printf("wait finish\n");
    TEST_ASSERT(bits == 0);

    stop_wifi();
}