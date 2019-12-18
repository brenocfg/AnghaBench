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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_BUS_MASTER_RLD ; 
 int /*<<< orphan*/  acpi_read_bit_register (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ saved_bm_rld ; 

__attribute__((used)) static void acpi_idle_bm_rld_restore(void)
{
	u32 resumed_bm_rld;

	acpi_read_bit_register(ACPI_BITREG_BUS_MASTER_RLD, &resumed_bm_rld);

	if (resumed_bm_rld != saved_bm_rld)
		acpi_write_bit_register(ACPI_BITREG_BUS_MASTER_RLD, saved_bm_rld);
}