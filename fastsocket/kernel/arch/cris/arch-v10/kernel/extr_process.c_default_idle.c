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
 int /*<<< orphan*/  etrax_gpio_wake_up_check () ; 

void default_idle(void)
{
#ifdef CONFIG_ETRAX_GPIO
  etrax_gpio_wake_up_check();
#endif
}