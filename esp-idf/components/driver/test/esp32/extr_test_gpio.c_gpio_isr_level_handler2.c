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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUTPUT_IO ; 
 int /*<<< orphan*/  ets_printf (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ gpio_get_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_level (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  level_intr_times ; 

__attribute__((used)) static void gpio_isr_level_handler2(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    level_intr_times++;
    ets_printf("GPIO[%d] intr, val: %d\n", gpio_num, gpio_get_level(gpio_num));
    if(gpio_get_level(gpio_num)) {
        gpio_set_level(GPIO_OUTPUT_IO, 0);
    }else{
        gpio_set_level(GPIO_OUTPUT_IO, 1);
    }
    ets_printf("GPIO[%d] intr, val: %d, level_intr_times = %d\n", GPIO_OUTPUT_IO, gpio_get_level(GPIO_OUTPUT_IO), level_intr_times);
    ets_printf("GPIO[%d] intr, val: %d, level_intr_times = %d\n", gpio_num, gpio_get_level(gpio_num), level_intr_times);
}