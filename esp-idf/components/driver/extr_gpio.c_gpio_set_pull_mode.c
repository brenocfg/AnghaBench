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
typedef  int gpio_pull_mode_t ;
typedef  int /*<<< orphan*/  gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  GPIO_CHECK (int,char*,int /*<<< orphan*/ ) ; 
#define  GPIO_FLOATING 131 
 int GPIO_IS_VALID_GPIO (int /*<<< orphan*/ ) ; 
#define  GPIO_PULLDOWN_ONLY 130 
#define  GPIO_PULLUP_ONLY 129 
#define  GPIO_PULLUP_PULLDOWN 128 
 int /*<<< orphan*/  GPIO_TAG ; 
 int /*<<< orphan*/  gpio_pulldown_dis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pulldown_en (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pullup_dis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pullup_en (int /*<<< orphan*/ ) ; 

esp_err_t gpio_set_pull_mode(gpio_num_t gpio_num, gpio_pull_mode_t pull)
{
    GPIO_CHECK(GPIO_IS_VALID_GPIO(gpio_num), "GPIO number error", ESP_ERR_INVALID_ARG);
    GPIO_CHECK(pull <= GPIO_FLOATING, "GPIO pull mode error", ESP_ERR_INVALID_ARG);
    esp_err_t ret = ESP_OK;
    switch (pull) {
    case GPIO_PULLUP_ONLY:
        gpio_pulldown_dis(gpio_num);
        gpio_pullup_en(gpio_num);
        break;
    case GPIO_PULLDOWN_ONLY:
        gpio_pulldown_en(gpio_num);
        gpio_pullup_dis(gpio_num);
        break;
    case GPIO_PULLUP_PULLDOWN:
        gpio_pulldown_en(gpio_num);
        gpio_pullup_en(gpio_num);
        break;
    case GPIO_FLOATING:
        gpio_pulldown_dis(gpio_num);
        gpio_pullup_dis(gpio_num);
        break;
    default:
        ESP_LOGE(GPIO_TAG, "Unknown pull up/down mode,gpio_num=%u,pull=%u", gpio_num, pull);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    return ret;
}