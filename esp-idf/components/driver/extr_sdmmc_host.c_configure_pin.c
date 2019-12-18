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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int GPIO_NUM_NC ; 
 scalar_t__* GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (scalar_t__,int const) ; 
 int /*<<< orphan*/  PIN_INPUT_ENABLE (scalar_t__) ; 
 int /*<<< orphan*/  PIN_SET_DRV (scalar_t__,int const) ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gpio_pulldown_dis (int) ; 

__attribute__((used)) static void configure_pin(int pin)
{
    const int sdmmc_func = 3;
    const int drive_strength = 3;
    assert(pin!=GPIO_NUM_NC);
    gpio_pulldown_dis(pin);

    uint32_t reg = GPIO_PIN_MUX_REG[pin];
    assert(reg != UINT32_MAX);
    PIN_INPUT_ENABLE(reg);
    PIN_FUNC_SELECT(reg, sdmmc_func);
    PIN_SET_DRV(reg, drive_strength);
}