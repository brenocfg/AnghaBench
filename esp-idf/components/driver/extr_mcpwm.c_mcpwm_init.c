#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mcpwm_unit_t ;
typedef  size_t mcpwm_timer_t ;
struct TYPE_14__ {int /*<<< orphan*/  duty_mode; int /*<<< orphan*/  cmpr_b; int /*<<< orphan*/  cmpr_a; int /*<<< orphan*/  counter_mode; int /*<<< orphan*/  frequency; } ;
typedef  TYPE_6__ mcpwm_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_13__ {int global_up_en; int global_force_up; } ;
struct TYPE_12__ {int operator1_sel; int operator2_sel; scalar_t__ operator0_sel; } ;
struct TYPE_9__ {int /*<<< orphan*/  prescale; } ;
struct TYPE_15__ {TYPE_5__ update_cfg; TYPE_4__ timer_sel; TYPE_3__* timer; TYPE_1__ clk_cfg; } ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_11__ {TYPE_2__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_8__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCPWM_CLK_PRESCL ; 
 int /*<<< orphan*/  MCPWM_TIMER_ERROR ; 
 size_t MCPWM_TIMER_MAX ; 
 size_t MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 scalar_t__ PERIPH_PWM0_MODULE ; 
 int /*<<< orphan*/  mcpwm_set_duty (size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_set_duty_type (size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_set_frequency (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_spinlock ; 
 int /*<<< orphan*/  mcpwm_start (size_t,size_t) ; 
 int /*<<< orphan*/  periph_module_enable (scalar_t__) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_init(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, const mcpwm_config_t *mcpwm_conf)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    MCPWM_CHECK(timer_num < MCPWM_TIMER_MAX, MCPWM_TIMER_ERROR, ESP_ERR_INVALID_ARG);
    periph_module_enable(PERIPH_PWM0_MODULE + mcpwm_num);
    portENTER_CRITICAL(&mcpwm_spinlock);
    MCPWM[mcpwm_num]->clk_cfg.prescale = MCPWM_CLK_PRESCL;
    mcpwm_set_frequency(mcpwm_num, timer_num, mcpwm_conf->frequency);
    MCPWM[mcpwm_num]->timer[timer_num].mode.mode = mcpwm_conf ->counter_mode;
    mcpwm_set_duty(mcpwm_num, timer_num, 0, mcpwm_conf->cmpr_a);
    mcpwm_set_duty(mcpwm_num, timer_num, 1, mcpwm_conf->cmpr_b);
    mcpwm_set_duty_type(mcpwm_num, timer_num, 0, mcpwm_conf->duty_mode);
    mcpwm_set_duty_type(mcpwm_num, timer_num, 1, mcpwm_conf->duty_mode);
    mcpwm_start(mcpwm_num, timer_num);
    MCPWM[mcpwm_num]->timer_sel.operator0_sel = 0;
    MCPWM[mcpwm_num]->timer_sel.operator1_sel = 1;
    MCPWM[mcpwm_num]->timer_sel.operator2_sel = 2;
    MCPWM[mcpwm_num]->update_cfg.global_up_en = 1;
    MCPWM[mcpwm_num]->update_cfg.global_force_up = 1;
    MCPWM[mcpwm_num]->update_cfg.global_force_up = 0;
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}