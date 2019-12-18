#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mcpwm_unit_t ;
typedef  size_t mcpwm_timer_t ;
struct TYPE_8__ {scalar_t__ carrier_os_mode; int /*<<< orphan*/  carrier_ivt_mode; int /*<<< orphan*/  pulse_width_in_os; int /*<<< orphan*/  carrier_duty; int /*<<< orphan*/  carrier_period; } ;
typedef  TYPE_3__ mcpwm_carrier_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_9__ {TYPE_2__* channel; } ;
struct TYPE_6__ {scalar_t__ in_invert; } ;
struct TYPE_7__ {TYPE_1__ carrier_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MCPWM_ONESHOT_MODE_EN ; 
 int /*<<< orphan*/  MCPWM_TIMER_ERROR ; 
 size_t MCPWM_TIMER_MAX ; 
 size_t MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  mcpwm_carrier_enable (size_t,size_t) ; 
 int /*<<< orphan*/  mcpwm_carrier_oneshot_mode_disable (size_t,size_t) ; 
 int /*<<< orphan*/  mcpwm_carrier_oneshot_mode_enable (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_output_invert (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_set_duty_cycle (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_set_period (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_carrier_init(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, const mcpwm_carrier_config_t *carrier_conf)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    MCPWM_CHECK(timer_num < MCPWM_TIMER_MAX, MCPWM_TIMER_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&mcpwm_spinlock);
    mcpwm_carrier_enable(mcpwm_num, timer_num);
    mcpwm_carrier_set_period(mcpwm_num, timer_num, carrier_conf->carrier_period);
    mcpwm_carrier_set_duty_cycle(mcpwm_num, timer_num, carrier_conf->carrier_duty);
    if (carrier_conf->carrier_os_mode == MCPWM_ONESHOT_MODE_EN) {
        mcpwm_carrier_oneshot_mode_enable(mcpwm_num, timer_num, carrier_conf->pulse_width_in_os);
    } else {
        mcpwm_carrier_oneshot_mode_disable(mcpwm_num, timer_num);
    }
    mcpwm_carrier_output_invert(mcpwm_num, timer_num, carrier_conf->carrier_ivt_mode);
    MCPWM[mcpwm_num]->channel[timer_num].carrier_cfg.in_invert = 0;
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}