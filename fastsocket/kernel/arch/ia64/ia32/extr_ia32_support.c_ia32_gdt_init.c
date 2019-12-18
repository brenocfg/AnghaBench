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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpu_gdt_table ; 
 int /*<<< orphan*/  ia32_boot_gdt ; 
 int /*<<< orphan*/ * ia32_shared_page ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int smp_processor_id () ; 

void
ia32_gdt_init (void)
{
	int cpu = smp_processor_id();

	ia32_shared_page[cpu] = alloc_page(GFP_KERNEL);
	if (!ia32_shared_page[cpu])
		panic("failed to allocate ia32_shared_page[%d]\n", cpu);

	cpu_gdt_table[cpu] = page_address(ia32_shared_page[cpu]);

	/* Copy from the boot cpu's GDT */
	memcpy(cpu_gdt_table[cpu], ia32_boot_gdt, PAGE_SIZE);
}