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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  adc_read_task ; 
 int /*<<< orphan*/  esp_log_level_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  example_i2s_adc_dac ; 
 int /*<<< orphan*/  example_i2s_init () ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

esp_err_t app_main(void)
{
    example_i2s_init();
    esp_log_level_set("I2S", ESP_LOG_INFO);
    xTaskCreate(example_i2s_adc_dac, "example_i2s_adc_dac", 1024 * 2, NULL, 5, NULL);
    xTaskCreate(adc_read_task, "ADC read task", 2048, NULL, 5, NULL);
    return ESP_OK;
}