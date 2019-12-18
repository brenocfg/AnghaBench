#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mcpwm_unit_t ;
typedef  int mcpwm_fault_signal_t ;
typedef  void* mcpwm_fault_input_level_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int f0_en; int f1_en; int f2_en; void* f2_pole; void* f1_pole; void* f0_pole; } ;
struct TYPE_4__ {TYPE_1__ fault_detect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MCPWM_SELECT_F0 130 
#define  MCPWM_SELECT_F1 129 
#define  MCPWM_SELECT_F2 128 
 scalar_t__ MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  mcpwm_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_fault_init(mcpwm_unit_t mcpwm_num, mcpwm_fault_input_level_t intput_level, mcpwm_fault_signal_t fault_sig)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&mcpwm_spinlock);
    switch (fault_sig) {
    case MCPWM_SELECT_F0:
        MCPWM[mcpwm_num]->fault_detect.f0_en = 1;
        MCPWM[mcpwm_num]->fault_detect.f0_pole = intput_level;
        break;
    case MCPWM_SELECT_F1:
        MCPWM[mcpwm_num]->fault_detect.f1_en = 1;
        MCPWM[mcpwm_num]->fault_detect.f1_pole = intput_level;
        break;
    case MCPWM_SELECT_F2:
        MCPWM[mcpwm_num]->fault_detect.f2_en = 1;
        MCPWM[mcpwm_num]->fault_detect.f2_pole = intput_level;

        break;
    default :
        break;
    }
    portEXIT_CRITICAL(&mcpwm_spinlock);
    return ESP_OK;
}