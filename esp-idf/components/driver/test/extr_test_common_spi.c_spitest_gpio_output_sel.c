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
typedef  size_t uint32_t ;
struct TYPE_4__ {TYPE_1__* func_out_sel_cfg; } ;
struct TYPE_3__ {size_t func_sel; } ;

/* Variables and functions */
 TYPE_2__ GPIO ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int) ; 

void spitest_gpio_output_sel(uint32_t gpio_num, int func, uint32_t signal_idx)
{
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[gpio_num], func);
    GPIO.func_out_sel_cfg[gpio_num].func_sel=signal_idx;
}