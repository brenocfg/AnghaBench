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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MODE_DEF_OUTPUT ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  PIN_FUNC_GPIO ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_matrix_out (int,int,int,int) ; 
 int /*<<< orphan*/  gpio_set_direction (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void gpio_matrix_out_check(uint32_t gpio, uint32_t signal_idx, bool out_inv, bool oen_inv)
{
    //if pin = -1, do not need to configure
    if (gpio != -1) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[gpio], PIN_FUNC_GPIO);
        gpio_set_direction(gpio, GPIO_MODE_DEF_OUTPUT);
        gpio_matrix_out(gpio, signal_idx, out_inv, oen_inv);
    }
}