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
typedef  scalar_t__ mcpwm_unit_t ;
struct TYPE_3__ {int /*<<< orphan*/  mcpwm_cap2_in_num; int /*<<< orphan*/  mcpwm_cap1_in_num; int /*<<< orphan*/  mcpwm_cap0_in_num; int /*<<< orphan*/  mcpwm_fault2_in_num; int /*<<< orphan*/  mcpwm_fault1_in_num; int /*<<< orphan*/  mcpwm_fault0_in_num; int /*<<< orphan*/  mcpwm_sync2_in_num; int /*<<< orphan*/  mcpwm_sync1_in_num; int /*<<< orphan*/  mcpwm_sync0_in_num; int /*<<< orphan*/  mcpwm2b_out_num; int /*<<< orphan*/  mcpwm2a_out_num; int /*<<< orphan*/  mcpwm1b_out_num; int /*<<< orphan*/  mcpwm1a_out_num; int /*<<< orphan*/  mcpwm0b_out_num; int /*<<< orphan*/  mcpwm0a_out_num; } ;
typedef  TYPE_1__ mcpwm_pin_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MCPWM0A ; 
 int /*<<< orphan*/  MCPWM0B ; 
 int /*<<< orphan*/  MCPWM1A ; 
 int /*<<< orphan*/  MCPWM1B ; 
 int /*<<< orphan*/  MCPWM2A ; 
 int /*<<< orphan*/  MCPWM2B ; 
 int /*<<< orphan*/  MCPWM_CAP_0 ; 
 int /*<<< orphan*/  MCPWM_CAP_1 ; 
 int /*<<< orphan*/  MCPWM_CAP_2 ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCPWM_FAULT_0 ; 
 int /*<<< orphan*/  MCPWM_SYNC_0 ; 
 int /*<<< orphan*/  MCPWM_SYNC_1 ; 
 int /*<<< orphan*/  MCPWM_SYNC_2 ; 
 scalar_t__ MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  mcpwm_gpio_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t mcpwm_set_pin(mcpwm_unit_t mcpwm_num, const mcpwm_pin_config_t *mcpwm_pin)
{
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    mcpwm_gpio_init(mcpwm_num, MCPWM0A, mcpwm_pin->mcpwm0a_out_num);    //MCPWM0A
    mcpwm_gpio_init(mcpwm_num, MCPWM0B, mcpwm_pin->mcpwm0b_out_num);    //MCPWM0B
    mcpwm_gpio_init(mcpwm_num, MCPWM1A, mcpwm_pin->mcpwm1a_out_num);    //MCPWM1A
    mcpwm_gpio_init(mcpwm_num, MCPWM1B, mcpwm_pin->mcpwm1b_out_num);    //MCPWM1B
    mcpwm_gpio_init(mcpwm_num, MCPWM2A, mcpwm_pin->mcpwm2a_out_num);    //MCPWM2A
    mcpwm_gpio_init(mcpwm_num, MCPWM2B, mcpwm_pin->mcpwm2b_out_num);    //MCPWM2B
    mcpwm_gpio_init(mcpwm_num, MCPWM_SYNC_0,  mcpwm_pin->mcpwm_sync0_in_num);   //SYNC0
    mcpwm_gpio_init(mcpwm_num, MCPWM_SYNC_1,  mcpwm_pin->mcpwm_sync1_in_num);   //SYNC1
    mcpwm_gpio_init(mcpwm_num, MCPWM_SYNC_2,  mcpwm_pin->mcpwm_sync2_in_num);   //SYNC2
    mcpwm_gpio_init(mcpwm_num, MCPWM_FAULT_0, mcpwm_pin->mcpwm_fault0_in_num);  //FAULT0
    mcpwm_gpio_init(mcpwm_num, MCPWM_FAULT_0, mcpwm_pin->mcpwm_fault1_in_num);  //FAULT1
    mcpwm_gpio_init(mcpwm_num, MCPWM_FAULT_0, mcpwm_pin->mcpwm_fault2_in_num);  //FAULT2
    mcpwm_gpio_init(mcpwm_num, MCPWM_CAP_0,   mcpwm_pin->mcpwm_cap0_in_num);    //CAP0
    mcpwm_gpio_init(mcpwm_num, MCPWM_CAP_1,   mcpwm_pin->mcpwm_cap1_in_num);    //CAP1
    mcpwm_gpio_init(mcpwm_num, MCPWM_CAP_2,   mcpwm_pin->mcpwm_cap2_in_num);    //CAP2
    return ESP_OK;
}