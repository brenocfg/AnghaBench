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
typedef  scalar_t__ dac_channel_t ;

/* Variables and functions */
 scalar_t__ DAC_CHANNEL_1 ; 
 scalar_t__ DAC_CHANNEL_MAX ; 
 int /*<<< orphan*/  DAC_ERR_STR_CHANNEL_ERROR ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_pad_get_io_num (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_gpio_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_input_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_output_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_pulldown_dis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_pullup_dis (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t dac_rtc_pad_init(dac_channel_t channel)
{
    RTC_MODULE_CHECK((channel >= DAC_CHANNEL_1) && (channel < DAC_CHANNEL_MAX), DAC_ERR_STR_CHANNEL_ERROR, ESP_ERR_INVALID_ARG);
    gpio_num_t gpio_num = 0;
    dac_pad_get_io_num(channel, &gpio_num);
    rtc_gpio_init(gpio_num);
    rtc_gpio_output_disable(gpio_num);
    rtc_gpio_input_disable(gpio_num);
    rtc_gpio_pullup_dis(gpio_num);
    rtc_gpio_pulldown_dis(gpio_num);

    return ESP_OK;
}