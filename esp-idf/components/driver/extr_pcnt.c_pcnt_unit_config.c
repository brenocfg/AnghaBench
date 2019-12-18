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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ unit; scalar_t__ channel; int pulse_gpio_num; int ctrl_gpio_num; int /*<<< orphan*/  lctrl_mode; int /*<<< orphan*/  hctrl_mode; int /*<<< orphan*/  neg_mode; int /*<<< orphan*/  pos_mode; int /*<<< orphan*/  counter_l_lim; int /*<<< orphan*/  counter_h_lim; } ;
typedef  TYPE_1__ pcnt_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ GPIO_IS_VALID_GPIO (int) ; 
 char* PCNT_CHANNEL_ERR_STR ; 
 scalar_t__ PCNT_CHANNEL_MAX ; 
 int /*<<< orphan*/  PCNT_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCNT_COUNT_MAX ; 
 char* PCNT_COUNT_MODE_ERR_STR ; 
 char* PCNT_CTRL_MODE_ERR_STR ; 
 int /*<<< orphan*/  PCNT_EVT_H_LIM ; 
 int /*<<< orphan*/  PCNT_EVT_L_LIM ; 
 int /*<<< orphan*/  PCNT_EVT_ZERO ; 
 int /*<<< orphan*/  PCNT_MODE_MAX ; 
 char* PCNT_UNIT_ERR_STR ; 
 scalar_t__ PCNT_UNIT_MAX ; 
 int /*<<< orphan*/  PERIPH_PCNT_MODULE ; 
 int /*<<< orphan*/  pcnt_event_disable (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnt_filter_disable (scalar_t__) ; 
 int /*<<< orphan*/  pcnt_set_event_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnt_set_mode (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnt_set_pin (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periph_module_reset (int /*<<< orphan*/ ) ; 

esp_err_t pcnt_unit_config(const pcnt_config_t *pcnt_config)
{
    uint8_t unit = pcnt_config->unit;
    uint8_t channel = pcnt_config->channel;
    int input_io = pcnt_config->pulse_gpio_num;
    int ctrl_io = pcnt_config->ctrl_gpio_num;

    PCNT_CHECK(unit < PCNT_UNIT_MAX, PCNT_UNIT_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(channel < PCNT_CHANNEL_MAX, PCNT_CHANNEL_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(input_io < 0 || (GPIO_IS_VALID_GPIO(input_io) && (input_io != ctrl_io)), "PCNT pulse input io error", ESP_ERR_INVALID_ARG);
    PCNT_CHECK(ctrl_io < 0 || GPIO_IS_VALID_GPIO(ctrl_io), "PCNT ctrl io error", ESP_ERR_INVALID_ARG);
    PCNT_CHECK((pcnt_config->pos_mode < PCNT_COUNT_MAX) && (pcnt_config->neg_mode < PCNT_COUNT_MAX), PCNT_COUNT_MODE_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK((pcnt_config->hctrl_mode < PCNT_MODE_MAX) && (pcnt_config->lctrl_mode < PCNT_MODE_MAX), PCNT_CTRL_MODE_ERR_STR, ESP_ERR_INVALID_ARG);
    /*Enalbe hardware module*/
    static bool pcnt_enable = false;
    if (pcnt_enable == false) {
        periph_module_reset(PERIPH_PCNT_MODULE);
        pcnt_enable = true;
    }
    periph_module_enable(PERIPH_PCNT_MODULE);
    /*Set counter range*/
    pcnt_set_event_value(unit, PCNT_EVT_H_LIM, pcnt_config->counter_h_lim);
    pcnt_set_event_value(unit, PCNT_EVT_L_LIM, pcnt_config->counter_l_lim);
    /*Default value after reboot is positive, we disable these events like others*/
    pcnt_event_disable(unit, PCNT_EVT_H_LIM);
    pcnt_event_disable(unit, PCNT_EVT_L_LIM);
    pcnt_event_disable(unit, PCNT_EVT_ZERO);
    pcnt_filter_disable(unit);
    /*set pulse input and control mode*/
    pcnt_set_mode(unit, channel, pcnt_config->pos_mode, pcnt_config->neg_mode, pcnt_config->hctrl_mode, pcnt_config->lctrl_mode);
    /*Set pulse input and control pins*/
    pcnt_set_pin(unit, channel, input_io, ctrl_io);
    return ESP_OK;
}