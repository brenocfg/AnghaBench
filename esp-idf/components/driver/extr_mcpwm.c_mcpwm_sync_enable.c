#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t mcpwm_unit_t ;
typedef  size_t mcpwm_timer_t ;
typedef  void* mcpwm_sync_signal_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {void* t2_in_sel; void* t1_in_sel; void* t0_in_sel; } ;
struct TYPE_10__ {TYPE_4__* timer; TYPE_2__ timer_synci_cfg; } ;
struct TYPE_8__ {int timer_phase; int in_en; scalar_t__ out_sel; } ;
struct TYPE_6__ {int period; } ;
struct TYPE_9__ {TYPE_3__ sync; TYPE_1__ period; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MCPWM_TIMER_0 ; 
 size_t MCPWM_TIMER_1 ; 
 int /*<<< orphan*/  MCPWM_TIMER_ERROR ; 
 size_t MCPWM_TIMER_MAX ; 
 size_t MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  mcpwm_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_sync_enable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_sync_signal_t sync_sig,
                            uint32_t phase_val)
{
    uint32_t set_phase;
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    MCPWM_CHECK(timer_num < MCPWM_TIMER_MAX, MCPWM_TIMER_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&mcpwm_spinlock);
    set_phase = (MCPWM[mcpwm_num]->timer[timer_num].period.period) * (phase_val) / 1000;
    MCPWM[mcpwm_num]->timer[timer_num].sync.timer_phase = set_phase;
    if (timer_num == MCPWM_TIMER_0) {
        MCPWM[mcpwm_num]->timer_synci_cfg.t0_in_sel = sync_sig;
    } else if (timer_num == MCPWM_TIMER_1) {
        MCPWM[mcpwm_num]->timer_synci_cfg.t1_in_sel = sync_sig;
    } else {   //MCPWM_TIMER_2
        MCPWM[mcpwm_num]->timer_synci_cfg.t2_in_sel = sync_sig;
    }
    MCPWM[mcpwm_num]->timer[timer_num].sync.out_sel = 0;
    MCPWM[mcpwm_num]->timer[timer_num].sync.in_en = 1;
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}