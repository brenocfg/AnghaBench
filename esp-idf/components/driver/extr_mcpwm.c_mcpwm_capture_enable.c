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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t mcpwm_unit_t ;
typedef  size_t mcpwm_capture_signal_t ;
typedef  int mcpwm_capture_on_edge_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int timer_en; } ;
struct TYPE_6__ {TYPE_1__* cap_cfg_ch; TYPE_2__ cap_timer_cfg; } ;
struct TYPE_4__ {int en; int mode; int /*<<< orphan*/  prescale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  mcpwm_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_capture_enable(mcpwm_unit_t mcpwm_num, mcpwm_capture_signal_t cap_sig, mcpwm_capture_on_edge_t cap_edge,
                               uint32_t num_of_pulse)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&mcpwm_spinlock);
    MCPWM[mcpwm_num]->cap_timer_cfg.timer_en = 1;
    MCPWM[mcpwm_num]->cap_cfg_ch[cap_sig].en = 1;
    MCPWM[mcpwm_num]->cap_cfg_ch[cap_sig].mode = (1 << cap_edge);
    MCPWM[mcpwm_num]->cap_cfg_ch[cap_sig].prescale = num_of_pulse;
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}