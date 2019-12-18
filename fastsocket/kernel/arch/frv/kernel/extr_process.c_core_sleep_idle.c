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
 int /*<<< orphan*/  __set_LEDS (int) ; 
 int /*<<< orphan*/  frv_cpu_core_sleep () ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void core_sleep_idle(void)
{
#ifdef LED_DEBUG_SLEEP
	/* Show that we're sleeping... */
	__set_LEDS(0x55aa);
#endif
	frv_cpu_core_sleep();
#ifdef LED_DEBUG_SLEEP
	/* ... and that we woke up */
	__set_LEDS(0);
#endif
	mb();
}