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
typedef  int adc2_channel_t ;

/* Variables and functions */
#define  ADC2_CHANNEL_0 137 
 int /*<<< orphan*/  ADC2_CHANNEL_0_GPIO_NUM ; 
#define  ADC2_CHANNEL_1 136 
 int /*<<< orphan*/  ADC2_CHANNEL_1_GPIO_NUM ; 
#define  ADC2_CHANNEL_2 135 
 int /*<<< orphan*/  ADC2_CHANNEL_2_GPIO_NUM ; 
#define  ADC2_CHANNEL_3 134 
 int /*<<< orphan*/  ADC2_CHANNEL_3_GPIO_NUM ; 
#define  ADC2_CHANNEL_4 133 
 int /*<<< orphan*/  ADC2_CHANNEL_4_GPIO_NUM ; 
#define  ADC2_CHANNEL_5 132 
 int /*<<< orphan*/  ADC2_CHANNEL_5_GPIO_NUM ; 
#define  ADC2_CHANNEL_6 131 
 int /*<<< orphan*/  ADC2_CHANNEL_6_GPIO_NUM ; 
#define  ADC2_CHANNEL_7 130 
 int /*<<< orphan*/  ADC2_CHANNEL_7_GPIO_NUM ; 
#define  ADC2_CHANNEL_8 129 
 int /*<<< orphan*/  ADC2_CHANNEL_8_GPIO_NUM ; 
#define  ADC2_CHANNEL_9 128 
 int /*<<< orphan*/  ADC2_CHANNEL_9_GPIO_NUM ; 
 int ADC2_CHANNEL_MAX ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 

esp_err_t adc2_pad_get_io_num(adc2_channel_t channel, gpio_num_t *gpio_num)
{
    RTC_MODULE_CHECK(channel < ADC2_CHANNEL_MAX, "ADC2 Channel Err", ESP_ERR_INVALID_ARG);

    switch (channel) {
    case ADC2_CHANNEL_0:
        *gpio_num = ADC2_CHANNEL_0_GPIO_NUM;
        break;
    case ADC2_CHANNEL_1:
        *gpio_num = ADC2_CHANNEL_1_GPIO_NUM;
        break;
    case ADC2_CHANNEL_2:
        *gpio_num = ADC2_CHANNEL_2_GPIO_NUM;
        break;
    case ADC2_CHANNEL_3:
        *gpio_num = ADC2_CHANNEL_3_GPIO_NUM;
        break;
    case ADC2_CHANNEL_4:
        *gpio_num = ADC2_CHANNEL_4_GPIO_NUM;
        break;
    case ADC2_CHANNEL_5:
        *gpio_num = ADC2_CHANNEL_5_GPIO_NUM;
        break;
    case ADC2_CHANNEL_6:
        *gpio_num = ADC2_CHANNEL_6_GPIO_NUM;
        break;
    case ADC2_CHANNEL_7:
        *gpio_num = ADC2_CHANNEL_7_GPIO_NUM;
        break;
    case ADC2_CHANNEL_8:
        *gpio_num = ADC2_CHANNEL_8_GPIO_NUM;
        break;
    case ADC2_CHANNEL_9:
        *gpio_num = ADC2_CHANNEL_9_GPIO_NUM;
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}