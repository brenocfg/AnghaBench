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

/* Variables and functions */
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  start_wifi_as_softap () ; 
 int /*<<< orphan*/  stop_wifi () ; 
 int /*<<< orphan*/  test_case_uses_tcpip () ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void receive_ds2ds_packet(void)
{
    test_case_uses_tcpip();
    start_wifi_as_softap();
    unity_wait_for_signal("sender ready");
    unity_send_signal("receiver ready");

    // wait for sender to send packets
    vTaskDelay(1000/portTICK_PERIOD_MS);
    stop_wifi();
}