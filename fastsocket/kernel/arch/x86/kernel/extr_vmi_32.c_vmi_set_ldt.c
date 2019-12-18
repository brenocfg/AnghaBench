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
struct desc_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* _set_ldt ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_LDT ; 
 int GDT_ENTRY_LDT ; 
 int /*<<< orphan*/  get_cpu_gdt_table (unsigned int) ; 
 int /*<<< orphan*/  pack_descriptor (struct desc_struct*,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_1__ vmi_ops ; 
 int /*<<< orphan*/  write_gdt_entry (int /*<<< orphan*/ ,int,struct desc_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmi_set_ldt(const void *addr, unsigned entries)
{
	unsigned cpu = smp_processor_id();
	struct desc_struct desc;

	pack_descriptor(&desc, (unsigned long)addr,
			entries * sizeof(struct desc_struct) - 1,
			DESC_LDT, 0);
	write_gdt_entry(get_cpu_gdt_table(cpu), GDT_ENTRY_LDT, &desc, DESC_LDT);
	vmi_ops._set_ldt(entries ? GDT_ENTRY_LDT*sizeof(struct desc_struct) : 0);
}