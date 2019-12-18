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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct acpi_resource_address64 {scalar_t__ address_length; scalar_t__ resource_type; scalar_t__ minimum; } ;
struct acpi_resource {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_BUS_NUMBER_RANGE ; 
 scalar_t__ ACPI_RESOURCE_TYPE_ADDRESS16 ; 
 scalar_t__ ACPI_RESOURCE_TYPE_ADDRESS32 ; 
 scalar_t__ ACPI_RESOURCE_TYPE_ADDRESS64 ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_resource_to_address64 (struct acpi_resource*,struct acpi_resource_address64*) ; 

__attribute__((used)) static acpi_status
get_root_bridge_busnr_callback(struct acpi_resource *resource, void *data)
{
	struct resource *res = data;
	struct acpi_resource_address64 address;

	if (resource->type != ACPI_RESOURCE_TYPE_ADDRESS16 &&
	    resource->type != ACPI_RESOURCE_TYPE_ADDRESS32 &&
	    resource->type != ACPI_RESOURCE_TYPE_ADDRESS64)
		return AE_OK;

	acpi_resource_to_address64(resource, &address);
	if ((address.address_length > 0) &&
	    (address.resource_type == ACPI_BUS_NUMBER_RANGE)) {
		res->start = address.minimum;
		res->end = address.minimum + address.address_length - 1;
	}

	return AE_OK;
}