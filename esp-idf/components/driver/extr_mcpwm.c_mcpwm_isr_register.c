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
typedef  scalar_t__ mcpwm_unit_t ;
typedef  int /*<<< orphan*/  intr_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 scalar_t__ ETS_PWM0_INTR_SOURCE ; 
 int /*<<< orphan*/  MCPWM_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCPWM_PARAM_ADDR_ERROR ; 
 scalar_t__ MCPWM_UNIT_MAX ; 
 int /*<<< orphan*/  MCPWM_UNIT_NUM_ERROR ; 
 int /*<<< orphan*/  esp_intr_alloc (scalar_t__,int,void (*) (void*),void*,int /*<<< orphan*/ *) ; 

esp_err_t mcpwm_isr_register(mcpwm_unit_t mcpwm_num, void (*fn)(void *), void *arg, int intr_alloc_flags, intr_handle_t *handle)
{
    esp_err_t ret;
    MCPWM_CHECK(mcpwm_num < MCPWM_UNIT_MAX, MCPWM_UNIT_NUM_ERROR, ESP_ERR_INVALID_ARG);
    MCPWM_CHECK(fn != NULL, MCPWM_PARAM_ADDR_ERROR, ESP_ERR_INVALID_ARG);
    ret = esp_intr_alloc((ETS_PWM0_INTR_SOURCE + mcpwm_num), intr_alloc_flags, fn, arg, handle);
    return ret;
}