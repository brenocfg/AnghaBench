#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ channel; int /*<<< orphan*/  sigmadelta_gpio; int /*<<< orphan*/  sigmadelta_prescale; int /*<<< orphan*/  sigmadelta_duty; } ;
typedef  TYPE_1__ sigmadelta_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int GPIO_IS_VALID_OUTPUT_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGMADELTA_CHANNEL_ERR_STR ; 
 scalar_t__ SIGMADELTA_CHANNEL_MAX ; 
 int /*<<< orphan*/  SIGMADELTA_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGMADELTA_IO_ERR_STR ; 
 int /*<<< orphan*/  sigmadelta_set_duty (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmadelta_set_pin (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmadelta_set_prescale (scalar_t__,int /*<<< orphan*/ ) ; 

esp_err_t sigmadelta_config(const sigmadelta_config_t *config)
{
    SIGMADELTA_CHECK(config->channel < SIGMADELTA_CHANNEL_MAX, SIGMADELTA_CHANNEL_ERR_STR, ESP_ERR_INVALID_ARG);
    SIGMADELTA_CHECK(GPIO_IS_VALID_OUTPUT_GPIO(config->sigmadelta_gpio), SIGMADELTA_IO_ERR_STR, ESP_ERR_INVALID_ARG);
    sigmadelta_set_duty(config->channel, config->sigmadelta_duty);
    sigmadelta_set_prescale(config->channel, config->sigmadelta_prescale);
    sigmadelta_set_pin(config->channel, config->sigmadelta_gpio);
    return ESP_OK;
}