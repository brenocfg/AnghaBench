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
struct acpi_generic_address {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_unmap_generic_address (struct acpi_generic_address*) ; 

__attribute__((used)) static inline void apei_unmap_generic_address(struct acpi_generic_address *reg)
{
	acpi_os_unmap_generic_address(reg);
}