#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  write_protect; } ;
struct TYPE_5__ {TYPE_1__ mem; } ;
struct acpi_resource_extended_address64 {scalar_t__ producer_consumer; scalar_t__ resource_type; int granularity; int /*<<< orphan*/  address_length; int /*<<< orphan*/  minimum; TYPE_2__ info; } ;
struct TYPE_6__ {struct acpi_resource_extended_address64 ext_address64; } ;
struct acpi_resource {TYPE_3__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DECODE_10 ; 
 int /*<<< orphan*/  ACPI_DECODE_16 ; 
 scalar_t__ ACPI_IO_RANGE ; 
 scalar_t__ ACPI_MEMORY_RANGE ; 
 scalar_t__ ACPI_PRODUCER ; 
 int /*<<< orphan*/  pnpacpi_parse_allocated_ioresource (struct pnp_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnpacpi_parse_allocated_memresource (struct pnp_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnpacpi_parse_allocated_ext_address_space(struct pnp_dev *dev,
						      struct acpi_resource *res)
{
	struct acpi_resource_extended_address64 *p = &res->data.ext_address64;

	if (p->producer_consumer == ACPI_PRODUCER)
		return;

	if (p->resource_type == ACPI_MEMORY_RANGE)
		pnpacpi_parse_allocated_memresource(dev,
			p->minimum, p->address_length,
			p->info.mem.write_protect);
	else if (p->resource_type == ACPI_IO_RANGE)
		pnpacpi_parse_allocated_ioresource(dev,
			p->minimum, p->address_length,
			p->granularity == 0xfff ? ACPI_DECODE_10 :
				ACPI_DECODE_16);
}