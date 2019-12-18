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
 int /*<<< orphan*/  PCCR ; 
 int /*<<< orphan*/  PCCR_E ; 
 int SYSREG_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int avr32_perf_counter_start(void)
{
	pr_debug("avr32_perf_counter_start\n");

	sysreg_write(PCCR, sysreg_read(PCCR) | SYSREG_BIT(PCCR_E));

	return 0;
}