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
struct acpi_ipmi_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_IPMI ; 
 int /*<<< orphan*/  IPMI_FLAGS_HANDLER_INSTALL ; 
 int /*<<< orphan*/  acpi_ipmi_space_handler ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmi_remove_space_handler(struct acpi_ipmi_device *ipmi)
{
	if (!test_bit(IPMI_FLAGS_HANDLER_INSTALL, &ipmi->flags))
		return;

	acpi_remove_address_space_handler(ipmi->handle,
				ACPI_ADR_SPACE_IPMI, &acpi_ipmi_space_handler);

	clear_bit(IPMI_FLAGS_HANDLER_INSTALL, &ipmi->flags);
}