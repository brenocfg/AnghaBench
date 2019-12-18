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
struct resource {char const* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; scalar_t__ start; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int acpi_check_resource_conflict (struct resource*) ; 

int acpi_check_mem_region(resource_size_t start, resource_size_t n,
		      const char *name)
{
	struct resource res = {
		.start = start,
		.end   = start + n - 1,
		.name  = name,
		.flags = IORESOURCE_MEM,
	};

	return acpi_check_resource_conflict(&res);

}