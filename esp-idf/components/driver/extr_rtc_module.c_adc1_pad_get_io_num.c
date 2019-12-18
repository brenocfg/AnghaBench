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
typedef  int adc1_channel_t ;

/* Variables and functions */
#define  ADC1_CHANNEL_0 135 
 int /*<<< orphan*/  ADC1_CHANNEL_0_GPIO_NUM ; 
#define  ADC1_CHANNEL_1 134 
 int /*<<< orphan*/  ADC1_CHANNEL_1_GPIO_NUM ; 
#define  ADC1_CHANNEL_2 133 
 int /*<<< orphan*/  ADC1_CHANNEL_2_GPIO_NUM ; 
#define  ADC1_CHANNEL_3 132 
 int /*<<< orphan*/  ADC1_CHANNEL_3_GPIO_NUM ; 
#define  ADC1_CHANNEL_4 131 
 int /*<<< orphan*/  ADC1_CHANNEL_4_GPIO_NUM ; 
#define  ADC1_CHANNEL_5 130 
 int /*<<< orphan*/  ADC1_CHANNEL_5_GPIO_NUM ; 
#define  ADC1_CHANNEL_6 129 
 int /*<<< orphan*/  ADC1_CHANNEL_6_GPIO_NUM ; 
#define  ADC1_CHANNEL_7 128 
 int /*<<< orphan*/  ADC1_CHANNEL_7_GPIO_NUM ; 
 int ADC1_CHANNEL_MAX ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 

esp_err_t adc1_pad_get_io_num(adc1_channel_t channel, gpio_num_t *gpio_num)
{
    RTC_MODULE_CHECK(channel < ADC1_CHANNEL_MAX, "ADC1 Channel Err", ESP_ERR_INVALID_ARG);

    switch (channel) {
    case ADC1_CHANNEL_0:
        *gpio_num = ADC1_CHANNEL_0_GPIO_NUM;
        break;
    case ADC1_CHANNEL_1:
        *gpio_num = ADC1_CHANNEL_1_GPIO_NUM;
        break;
    case ADC1_CHANNEL_2:
        *gpio_num = ADC1_CHANNEL_2_GPIO_NUM;
        break;
    case ADC1_CHANNEL_3:
        *gpio_num = ADC1_CHANNEL_3_GPIO_NUM;
        break;
    case ADC1_CHANNEL_4:
        *gpio_num = ADC1_CHANNEL_4_GPIO_NUM;
        break;
    case ADC1_CHANNEL_5:
        *gpio_num = ADC1_CHANNEL_5_GPIO_NUM;
        break;
    case ADC1_CHANNEL_6:
        *gpio_num = ADC1_CHANNEL_6_GPIO_NUM;
        break;
    case ADC1_CHANNEL_7:
        *gpio_num = ADC1_CHANNEL_7_GPIO_NUM;
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}