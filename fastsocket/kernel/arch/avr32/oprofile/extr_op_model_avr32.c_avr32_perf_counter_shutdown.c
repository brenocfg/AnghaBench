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
 int /*<<< orphan*/  AVR32_PERFCTR_IRQ_GROUP ; 
 int /*<<< orphan*/  avr32_perf_counter_reset () ; 
 int /*<<< orphan*/  counter ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void avr32_perf_counter_shutdown(void)
{
	pr_debug("avr32_perf_counter_shutdown\n");

	avr32_perf_counter_reset();
	free_irq(AVR32_PERFCTR_IRQ_GROUP, counter);
}