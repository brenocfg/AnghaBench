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
struct TYPE_2__ {struct desc_struct* gdt; } ;
struct lg_cpu {TYPE_1__ arch; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 unsigned int GDT_ENTRIES ; 
 int /*<<< orphan*/  ignored_gdt (unsigned int) ; 

void copy_gdt(const struct lg_cpu *cpu, struct desc_struct *gdt)
{
	unsigned int i;

	/*
	 * The default entries from setup_default_gdt_entries() are not
	 * replaced.  See ignored_gdt() above.
	 */
	for (i = 0; i < GDT_ENTRIES; i++)
		if (!ignored_gdt(i))
			gdt[i] = cpu->arch.gdt[i];
}