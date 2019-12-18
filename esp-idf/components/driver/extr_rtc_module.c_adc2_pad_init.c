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
typedef  int /*<<< orphan*/  gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  adc2_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC2_CHECK_FUNCTION_RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  GPIO_FLOATING ; 
 int /*<<< orphan*/  adc2_pad_get_io_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_set_pull_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_input_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_output_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t adc2_pad_init(adc2_channel_t channel)
{
    gpio_num_t gpio_num = 0;
    ADC2_CHECK_FUNCTION_RET(adc2_pad_get_io_num(channel, &gpio_num));
    ADC2_CHECK_FUNCTION_RET(rtc_gpio_init(gpio_num));
    ADC2_CHECK_FUNCTION_RET(rtc_gpio_output_disable(gpio_num));
    ADC2_CHECK_FUNCTION_RET(rtc_gpio_input_disable(gpio_num));
    ADC2_CHECK_FUNCTION_RET(gpio_set_pull_mode(gpio_num, GPIO_FLOATING));
    return ESP_OK;
}