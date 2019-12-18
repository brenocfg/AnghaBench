#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mcpwm_unit_t ;
typedef  size_t mcpwm_timer_t ;
typedef  scalar_t__ mcpwm_fault_signal_t ;
typedef  void* mcpwm_action_on_pwmxb_t ;
typedef  void* mcpwm_action_on_pwmxa_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {TYPE_3__* channel; } ;
struct TYPE_6__ {int f0_cbc; int f1_cbc; int f2_cbc; void* b_cbc_u; void* b_cbc_d; void* a_cbc_u; void* a_cbc_d; scalar_t__ f2_ost; scalar_t__ f1_ost; scalar_t__ f0_ost; } ;
struct TYPE_5__ {int /*<<< orphan*/  cbcpulse; } ;
struct TYPE_7__ {TYPE_2__ tz_cfg0; TYPE_1__ tz_cfg1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_4__** MCPWM ; 
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

esp_err_t mcpwm_fault_set_cyc_mode(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_fault_signal_t fault_sig,
                                   mcpwm_action_on_pwmxa_t action_on_pwmxa, mcpwm_action_on_pwmxb_t action_on_pwmxb)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    MCPWM_CHECK(timer_num < MCPWM_TIMER_MAX, MCPWM_TIMER_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&mcpwm_spinlock);
    MCPWM[mcpwm_num]->channel[timer_num].tz_cfg1.cbcpulse = BIT(0);
    if (fault_sig == MCPWM_SELECT_F0) {
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f0_cbc = 1;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f0_ost = 0;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_cbc_d = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_cbc_u = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_cbc_d = action_on_pwmxb;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_cbc_u = action_on_pwmxb;
    } else if (fault_sig == MCPWM_SELECT_F1) {
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f1_cbc = 1;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f1_ost = 0;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_cbc_d = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_cbc_u = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_cbc_d = action_on_pwmxb;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_cbc_u = action_on_pwmxb;
    } else {  //MCPWM_SELECT_F2
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f2_cbc = 1;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.f2_ost = 0;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_cbc_d = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.a_cbc_u = action_on_pwmxa;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_cbc_d = action_on_pwmxb;
        MCPWM[mcpwm_num]->channel[timer_num].tz_cfg0.b_cbc_u = action_on_pwmxb;
    }
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}