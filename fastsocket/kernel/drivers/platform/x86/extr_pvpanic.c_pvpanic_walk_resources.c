#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  minimum; } ;
struct TYPE_4__ {TYPE_1__ io; } ;
struct acpi_resource {int type; TYPE_2__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_END_TAG 129 
#define  ACPI_RESOURCE_TYPE_IO 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  port ; 

__attribute__((used)) static acpi_status
pvpanic_walk_resources(struct acpi_resource *res, void *context)
{
	switch (res->type) {
	case ACPI_RESOURCE_TYPE_END_TAG:
		return AE_OK;

	case ACPI_RESOURCE_TYPE_IO:
		port = res->data.io.minimum;
		return AE_OK;

	default:
		return AE_ERROR;
	}
}