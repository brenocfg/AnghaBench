#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mcpwm_unit_t ;
typedef  size_t mcpwm_timer_t ;
typedef  scalar_t__ mcpwm_fault_signal_t ;
typedef  void* mcpwm_action_on_pwmxb_t ;
typedef  void* mcpwm_action_on_pwmxa_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_2__* channel; } ;
struct TYPE_4__ {int f0_ost; int f1_ost; int f2_ost; void* b_ost_u; void* b_ost_d; void* a_ost_u; void* a_ost_d; scalar_t__ f2_cbc; scalar_t__ f1_cbc; scalar_t__ f0_cbc; } ;
struct TYPE_5__ {TYPE_1__ tz_cfg0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MCPWM_SELECT_F0 ; 
 scalar_t__ MCPWM_SELECT_F1 ; 
 int /*<<< orphan*/  MCPWM_TIMER_ERROR ; 
 size_t MCPWM_TIMER_MAX ; 
 size_t MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  mcpwm_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_fault_set_oneshot_mode(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_fault_signal_t fault_sig,
                                       mcpwm_action_on_pwmxa_t action_on_pwmxa, mcpwm_action_on_pwmxb_t action_on_pwmxb)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    MCPWM_CHECK(timer_num < MCPWM_TIMER_MAX, MCPWM_TIMER_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&mcpwm_spinlock);
    if (fault_sig == MCPWM_SELECT_F0) {
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f0_ost = 1;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f0_cbc = 0;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_ost_d = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_ost_u = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_ost_d = action_on_pwmxb;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_ost_u = action_on_pwmxb;
    } else if (fault_sig == MCPWM_SELECT_F1) {
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f1_ost = 1;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f1_cbc = 0;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_ost_d = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_ost_u = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_ost_d = action_on_pwmxb;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_ost_u = action_on_pwmxb;
    } else {   //MCPWM_SELECT_F2
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f2_ost = 1;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f2_cbc = 0;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_ost_d = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_ost_u = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_ost_d = action_on_pwmxb;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_ost_u = action_on_pwmxb;
    }
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}