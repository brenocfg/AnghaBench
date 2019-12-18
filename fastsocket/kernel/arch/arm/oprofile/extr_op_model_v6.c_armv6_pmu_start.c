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
 int arm11_request_interrupts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int arm11_start_pmu () ; 
 int /*<<< orphan*/  irqs ; 

__attribute__((used)) static int armv6_pmu_start(void)
{
	int ret;

	ret = arm11_request_interrupts(irqs, ARRAY_SIZE(irqs));
	if (ret >= 0)
		ret = arm11_start_pmu();

	return ret;
}