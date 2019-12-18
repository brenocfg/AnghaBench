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
typedef  int pcnt_unit_t ;
typedef  scalar_t__ pcnt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ GPIO_IS_VALID_GPIO (int) ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  GPIO_PULLUP_ONLY ; 
 int /*<<< orphan*/  PCNT_CHANNEL_ERR_STR ; 
 scalar_t__ PCNT_CHANNEL_MAX ; 
 int /*<<< orphan*/  PCNT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCNT_CTRL_CH0_IN0_IDX ; 
 int PCNT_CTRL_CH1_IN0_IDX ; 
 int /*<<< orphan*/  PCNT_GPIO_ERR_STR ; 
 int PCNT_SIG_CH0_IN0_IDX ; 
 int PCNT_SIG_CH1_IN0_IDX ; 
 int /*<<< orphan*/  PCNT_UNIT_ERR_STR ; 
 int PCNT_UNIT_MAX ; 
 int /*<<< orphan*/  PIN_FUNC_GPIO ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_matrix_in (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_direction (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_pull_mode (int,int /*<<< orphan*/ ) ; 

esp_err_t pcnt_set_pin(pcnt_unit_t unit, pcnt_channel_t channel, int pulse_io, int ctrl_io)
{
    PCNT_CHECK(unit < PCNT_UNIT_MAX, PCNT_UNIT_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(channel < PCNT_CHANNEL_MAX, PCNT_CHANNEL_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(GPIO_IS_VALID_GPIO(pulse_io) || pulse_io < 0, PCNT_GPIO_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(GPIO_IS_VALID_GPIO(ctrl_io) || ctrl_io < 0, PCNT_GPIO_ERR_STR, ESP_ERR_INVALID_ARG);

    int sig_base  = (channel == 0) ? PCNT_SIG_CH0_IN0_IDX  : PCNT_SIG_CH1_IN0_IDX;
    int ctrl_base = (channel == 0) ? PCNT_CTRL_CH0_IN0_IDX : PCNT_CTRL_CH1_IN0_IDX;
    if (unit > 4) {
        sig_base  += 12; // GPIO matrix assignments have a gap between units 4 & 5
        ctrl_base += 12;
    }
    int input_sig_index = sig_base  + (4 * unit);
    int ctrl_sig_index  = ctrl_base + (4 * unit);

    if(pulse_io >= 0) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[pulse_io], PIN_FUNC_GPIO);
        gpio_set_direction(pulse_io, GPIO_MODE_INPUT);
        gpio_set_pull_mode(pulse_io, GPIO_PULLUP_ONLY);
        gpio_matrix_in(pulse_io, input_sig_index, 0);
    }
    if(ctrl_io >= 0) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[ctrl_io], PIN_FUNC_GPIO);
        gpio_set_direction(ctrl_io, GPIO_MODE_INPUT);
        gpio_set_pull_mode(ctrl_io, GPIO_PULLUP_ONLY);
        gpio_matrix_in(ctrl_io, ctrl_sig_index, 0);
    }
    return ESP_OK;
}