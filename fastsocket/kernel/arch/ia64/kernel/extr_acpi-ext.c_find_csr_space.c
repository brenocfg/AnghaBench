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
struct csr_space {scalar_t__ length; int /*<<< orphan*/  base; } ;
struct acpi_resource_address64 {scalar_t__ resource_type; scalar_t__ producer_consumer; scalar_t__ address_length; int /*<<< orphan*/  minimum; } ;
struct acpi_resource {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_CONSUMER ; 
 scalar_t__ ACPI_MEMORY_RANGE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_resource_to_address64 (struct acpi_resource*,struct acpi_resource_address64*) ; 

__attribute__((used)) static acpi_status find_csr_space(struct acpi_resource *resource, void *data)
{
	struct csr_space *space = data;
	struct acpi_resource_address64 addr;
	acpi_status status;

	status = acpi_resource_to_address64(resource, &addr);
	if (ACPI_SUCCESS(status) &&
	    addr.resource_type == ACPI_MEMORY_RANGE &&
	    addr.address_length &&
	    addr.producer_consumer == ACPI_CONSUMER) {
		space->base = addr.minimum;
		space->length = addr.address_length;
		return AE_CTRL_TERMINATE;
	}
	return AE_OK;		/* keep looking */
}