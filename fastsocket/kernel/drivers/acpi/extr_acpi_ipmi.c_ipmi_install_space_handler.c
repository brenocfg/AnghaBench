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
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct acpi_ipmi_device {int /*<<< orphan*/  flags; struct pnp_dev* pnp_dev; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_IPMI ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPMI_FLAGS_HANDLER_INSTALL ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  acpi_ipmi_space_handler ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmi_install_space_handler(struct acpi_ipmi_device *ipmi)
{
	acpi_status status;

	if (test_bit(IPMI_FLAGS_HANDLER_INSTALL, &ipmi->flags))
		return 0;

	status = acpi_install_address_space_handler(ipmi->handle,
						    ACPI_ADR_SPACE_IPMI,
						    &acpi_ipmi_space_handler,
						    NULL, ipmi);
	if (ACPI_FAILURE(status)) {
		struct pnp_dev *pnp_dev = ipmi->pnp_dev;
		dev_warn(&pnp_dev->dev, "Can't register IPMI opregion space "
			"handle\n");
		return -EINVAL;
	}
	set_bit(IPMI_FLAGS_HANDLER_INSTALL, &ipmi->flags);
	return 0;
}