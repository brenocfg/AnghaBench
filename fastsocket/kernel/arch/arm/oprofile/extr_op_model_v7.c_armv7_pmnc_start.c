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
 int /*<<< orphan*/  armv7_pmnc_dump_regs () ; 
 int armv7_request_interrupts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armv7_start_pmnc () ; 
 int /*<<< orphan*/  irqs ; 

__attribute__((used)) static int armv7_pmnc_start(void)
{
	int ret;

#ifdef DEBUG
	armv7_pmnc_dump_regs();
#endif
	ret = armv7_request_interrupts(irqs, ARRAY_SIZE(irqs));
	if (ret >= 0)
		armv7_start_pmnc();

	return ret;
}