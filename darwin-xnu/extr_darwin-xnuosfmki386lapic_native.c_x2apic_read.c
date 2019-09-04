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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lapic_register_t ;

/* Variables and functions */
 int /*<<< orphan*/  LAPIC_MSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
x2apic_read(lapic_register_t reg)
{
	uint32_t	lo;
	uint32_t	hi;

	rdmsr(LAPIC_MSR(reg), lo, hi);
	return lo;
}