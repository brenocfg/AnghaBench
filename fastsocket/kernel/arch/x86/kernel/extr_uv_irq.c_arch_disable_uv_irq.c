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
struct uv_IO_APIC_route_entry {int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  uv_write_global_mmr64 (int,unsigned long,unsigned long) ; 

__attribute__((used)) static void arch_disable_uv_irq(int mmr_pnode, unsigned long mmr_offset)
{
	unsigned long mmr_value;
	struct uv_IO_APIC_route_entry *entry;

	BUILD_BUG_ON(sizeof(struct uv_IO_APIC_route_entry) !=
			sizeof(unsigned long));

	mmr_value = 0;
	entry = (struct uv_IO_APIC_route_entry *)&mmr_value;
	entry->mask = 1;

	uv_write_global_mmr64(mmr_pnode, mmr_offset, mmr_value);
}