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
 int /*<<< orphan*/  AR9170_GPIO_REG_PORT_DATA ; 
 int get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_timer () ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlan_timer () ; 

__attribute__((used)) static void timer0_isr(void)
{
	wlan_timer();

#ifdef CONFIG_CARL9170FW_GPIO_INTERRUPT
	gpio_timer();
#endif /* CONFIG_CARL9170FW_GPIO_INTERRUPT */

#ifdef CONFIG_CARL9170FW_DEBUG_LED_HEARTBEAT
	set(AR9170_GPIO_REG_PORT_DATA, get(AR9170_GPIO_REG_PORT_DATA) ^ 1);
#endif /* CONFIG_CARL9170FW_DEBUG_LED_HEARTBEAT */
}