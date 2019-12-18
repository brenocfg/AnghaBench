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
struct resource {int flags; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ BIOS_END ; 
 int /*<<< orphan*/  BIOS_ROM_BASE ; 
 int /*<<< orphan*/  BIOS_ROM_END ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  remove_e820_regions (struct resource*) ; 
 int /*<<< orphan*/  resource_clip (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void arch_remove_reservations(struct resource *avail)
{
	/* Trim out BIOS areas (low 1MB and high 2MB) and E820 regions */
	if (avail->flags & IORESOURCE_MEM) {
		if (avail->start < BIOS_END)
			avail->start = BIOS_END;
		resource_clip(avail, BIOS_ROM_BASE, BIOS_ROM_END);

		remove_e820_regions(avail);
	}
}