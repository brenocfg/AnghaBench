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
struct acpi_processor_cx {int valid; int /*<<< orphan*/  latency; int /*<<< orphan*/  latency_ticks; int /*<<< orphan*/  address; } ;

/* Variables and functions */

__attribute__((used)) static void acpi_processor_power_verify_c2(struct acpi_processor_cx *cx)
{

	if (!cx->address)
		return;

	/*
	 * Otherwise we've met all of our C2 requirements.
	 * Normalize the C2 latency to expidite policy
	 */
	cx->valid = 1;

	cx->latency_ticks = cx->latency;

	return;
}