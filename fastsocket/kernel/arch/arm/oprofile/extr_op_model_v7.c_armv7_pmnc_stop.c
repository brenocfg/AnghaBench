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
 int /*<<< orphan*/  armv7_release_interrupts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armv7_stop_pmnc () ; 
 int /*<<< orphan*/  irqs ; 

__attribute__((used)) static void armv7_pmnc_stop(void)
{
#ifdef DEBUG
	armv7_pmnc_dump_regs();
#endif
	armv7_stop_pmnc();
	armv7_release_interrupts(irqs, ARRAY_SIZE(irqs));
}