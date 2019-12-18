#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int bit_offset; } ;
struct acpi_whea_header {int mask; TYPE_1__ register_region; } ;

/* Variables and functions */
 int apei_read (int*,TYPE_1__*) ; 

int __apei_exec_read_register(struct acpi_whea_header *entry, u64 *val)
{
	int rc;

	rc = apei_read(val, &entry->register_region);
	if (rc)
		return rc;
	*val >>= entry->register_region.bit_offset;
	*val &= entry->mask;

	return 0;
}