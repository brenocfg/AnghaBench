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
typedef  int dac_channel_t ;

/* Variables and functions */
#define  DAC_CHANNEL_1 129 
 int /*<<< orphan*/  DAC_CHANNEL_1_GPIO_NUM ; 
#define  DAC_CHANNEL_2 128 
 int /*<<< orphan*/  DAC_CHANNEL_2_GPIO_NUM ; 
 int DAC_CHANNEL_MAX ; 
 int /*<<< orphan*/  DAC_ERR_STR_CHANNEL_ERROR ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 

esp_err_t dac_pad_get_io_num(dac_channel_t channel, gpio_num_t *gpio_num)
{
    RTC_MODULE_CHECK((channel >= DAC_CHANNEL_1) && (channel < DAC_CHANNEL_MAX), DAC_ERR_STR_CHANNEL_ERROR, ESP_ERR_INVALID_ARG);
    RTC_MODULE_CHECK(gpio_num, "Param null", ESP_ERR_INVALID_ARG);

    switch (channel) {
    case DAC_CHANNEL_1:
        *gpio_num = DAC_CHANNEL_1_GPIO_NUM;
        break;
    case DAC_CHANNEL_2:
        *gpio_num = DAC_CHANNEL_2_GPIO_NUM;
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}