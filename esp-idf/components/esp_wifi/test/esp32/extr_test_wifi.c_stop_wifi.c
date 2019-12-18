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
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_deinit () ; 
 int /*<<< orphan*/  esp_wifi_stop () ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vEventGroupDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/ * wifi_events ; 

__attribute__((used)) static void stop_wifi(void)
{
    printf("stop wifi\n");
    TEST_ESP_OK(esp_wifi_stop());
    TEST_ESP_OK(esp_wifi_deinit());
    if (wifi_events) {
        vEventGroupDelete(wifi_events);
        wifi_events = NULL;
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
}