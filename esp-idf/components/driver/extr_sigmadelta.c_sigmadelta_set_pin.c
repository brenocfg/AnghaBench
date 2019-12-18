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
typedef  scalar_t__ sigmadelta_channel_t ;
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int GPIO_IS_VALID_OUTPUT_GPIO (size_t) ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 scalar_t__ GPIO_SD0_OUT_IDX ; 
 int /*<<< orphan*/  PIN_FUNC_GPIO ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGMADELTA_CHANNEL_ERR_STR ; 
 scalar_t__ SIGMADELTA_CHANNEL_MAX ; 
 int /*<<< orphan*/  SIGMADELTA_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGMADELTA_IO_ERR_STR ; 
 int /*<<< orphan*/  gpio_matrix_out (size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_direction (size_t,int /*<<< orphan*/ ) ; 

esp_err_t sigmadelta_set_pin(sigmadelta_channel_t channel, gpio_num_t gpio_num)
{
    SIGMADELTA_CHECK(channel < SIGMADELTA_CHANNEL_MAX, SIGMADELTA_CHANNEL_ERR_STR, ESP_ERR_INVALID_ARG);
    SIGMADELTA_CHECK(GPIO_IS_VALID_OUTPUT_GPIO(gpio_num), SIGMADELTA_IO_ERR_STR, ESP_ERR_INVALID_ARG);
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[gpio_num], PIN_FUNC_GPIO);
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
    gpio_matrix_out(gpio_num, GPIO_SD0_OUT_IDX + channel, 0, 0);
    return ESP_OK;
}