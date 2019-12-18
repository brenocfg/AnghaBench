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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm11_irqs ; 
 int /*<<< orphan*/  arm11_release_interrupts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm11_stop_pmu ; 
 int /*<<< orphan*/  em_call_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scu_stop () ; 

__attribute__((used)) static void em_stop(void)
{
	em_call_function(arm11_stop_pmu);
	arm11_release_interrupts(arm11_irqs, ARRAY_SIZE(arm11_irqs));
	scu_stop();
}