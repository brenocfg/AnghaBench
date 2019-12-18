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
typedef  int u32 ;

/* Variables and functions */
 int ACPI_PM_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmtmr_ioport ; 

__attribute__((used)) static unsigned pmtimer_wait_tick(void)
{
	u32 a, b;
	for (a = b = inl(pmtmr_ioport) & ACPI_PM_MASK;
	     a == b;
	     b = inl(pmtmr_ioport) & ACPI_PM_MASK)
		cpu_relax();
	return b;
}