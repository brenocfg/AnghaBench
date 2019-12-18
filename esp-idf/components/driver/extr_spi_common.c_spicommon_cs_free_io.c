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

/* Variables and functions */
 scalar_t__ GPIO_IS_VALID_GPIO (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gpio_reset_pin (int) ; 

void spicommon_cs_free_io(int cs_gpio_num)
{
    assert(cs_gpio_num>=0 && GPIO_IS_VALID_GPIO(cs_gpio_num));
    gpio_reset_pin(cs_gpio_num);
}