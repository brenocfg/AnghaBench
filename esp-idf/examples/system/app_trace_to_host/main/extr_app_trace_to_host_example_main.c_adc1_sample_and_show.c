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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1_TEST_CHANNEL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  adc1_get_raw (int /*<<< orphan*/ ) ; 
 int esp_log_timestamp () ; 

__attribute__((used)) static int adc1_sample_and_show(int sampling_period)
{
    int i = 0;
    uint32_t sampling_start = esp_log_timestamp();
    do {
        ESP_LOGI(TAG, "Sample:%d, Value:%d", ++i, adc1_get_raw(ADC1_TEST_CHANNEL));
    } while (esp_log_timestamp() - sampling_start < sampling_period);
    return i;
}