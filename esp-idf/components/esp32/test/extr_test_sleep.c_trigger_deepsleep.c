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
 int esp_clk_slowclk_cal_get () ; 
 int /*<<< orphan*/  esp_clk_slowclk_cal_set (int) ; 
 int /*<<< orphan*/  esp_deep_sleep_start () ; 
 int /*<<< orphan*/  esp_set_time_from_rtc () ; 
 int /*<<< orphan*/  esp_sleep_enable_timer_wakeup (int) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void trigger_deepsleep(void)
{
    printf("Trigger deep sleep. Waiting for 10 sec ...\n");

    // Simulate the dispersion of the calibration coefficients at start-up.
    // Corrupt the calibration factor.
    esp_clk_slowclk_cal_set(esp_clk_slowclk_cal_get() / 2);
    esp_set_time_from_rtc();

    // Delay for time error accumulation.
    vTaskDelay(10000/portTICK_RATE_MS);

    // Save start time. Deep sleep.
    gettimeofday(&start, NULL);
    esp_sleep_enable_timer_wakeup(1000);
    // In function esp_deep_sleep_start() uses function esp_sync_counters_rtc_and_frc()
    // to prevent a negative time after wake up.
    esp_deep_sleep_start();
}