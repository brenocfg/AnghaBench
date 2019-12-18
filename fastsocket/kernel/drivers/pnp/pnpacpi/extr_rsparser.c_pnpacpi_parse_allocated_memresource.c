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
typedef  scalar_t__ u64 ;
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int ACPI_READ_WRITE_MEMORY ; 
 int IORESOURCE_DISABLED ; 
 int IORESOURCE_MEM_WRITEABLE ; 
 int /*<<< orphan*/  pnp_add_mem_resource (struct pnp_dev*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void pnpacpi_parse_allocated_memresource(struct pnp_dev *dev,
						u64 start, u64 len,
						int write_protect)
{
	int flags = 0;
	u64 end = start + len - 1;

	if (len == 0)
		flags |= IORESOURCE_DISABLED;
	if (write_protect == ACPI_READ_WRITE_MEMORY)
		flags |= IORESOURCE_MEM_WRITEABLE;

	pnp_add_mem_resource(dev, start, end, flags);
}