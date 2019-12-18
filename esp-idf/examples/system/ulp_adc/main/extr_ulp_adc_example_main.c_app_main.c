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
typedef  scalar_t__ esp_sleep_wakeup_cause_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_SLEEP_WAKEUP_ULP ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  esp_deep_sleep_start () ; 
 int /*<<< orphan*/  esp_sleep_enable_ulp_wakeup () ; 
 scalar_t__ esp_sleep_get_wakeup_cause () ; 
 int /*<<< orphan*/  init_ulp_program () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  start_ulp_program () ; 
 int ulp_high_thr ; 
 int ulp_last_result ; 
 int ulp_low_thr ; 
 int ulp_sample_counter ; 

void app_main(void)
{
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    if (cause != ESP_SLEEP_WAKEUP_ULP) {
        printf("Not ULP wakeup\n");
        init_ulp_program();
    } else {
        printf("Deep sleep wakeup\n");
        printf("ULP did %d measurements since last reset\n", ulp_sample_counter & UINT16_MAX);
        printf("Thresholds:  low=%d  high=%d\n", ulp_low_thr, ulp_high_thr);
        ulp_last_result &= UINT16_MAX;
        printf("Value=%d was %s threshold\n", ulp_last_result,
                ulp_last_result < ulp_low_thr ? "below" : "above");
    }
    printf("Entering deep sleep\n\n");
    start_ulp_program();
    ESP_ERROR_CHECK( esp_sleep_enable_ulp_wakeup() );
    esp_deep_sleep_start();
}