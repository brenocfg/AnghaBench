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
struct desc_ptr {unsigned long address; scalar_t__ size; } ;
struct TYPE_4__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 scalar_t__ GDT_SIZE ; 
 unsigned long X86_CR4_PAE ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 TYPE_2__* efi_bak_pg_dir_pointer ; 
 int /*<<< orphan*/  efi_rt_eflags ; 
 scalar_t__ get_cpu_gdt_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_gdt (struct desc_ptr*) ; 
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 
 size_t pgd_index (int) ; 
 unsigned long read_cr4_safe () ; 
 TYPE_1__* swapper_pg_dir ; 

void efi_call_phys_epilog(void)
{
	unsigned long cr4;
	struct desc_ptr gdt_descr;

	gdt_descr.address = (unsigned long)get_cpu_gdt_table(0);
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);

	cr4 = read_cr4_safe();

	if (cr4 & X86_CR4_PAE) {
		swapper_pg_dir[pgd_index(0)].pgd =
		    efi_bak_pg_dir_pointer[0].pgd;
	} else {
		swapper_pg_dir[pgd_index(0)].pgd =
		    efi_bak_pg_dir_pointer[0].pgd;
		swapper_pg_dir[pgd_index(0x400000)].pgd =
		    efi_bak_pg_dir_pointer[1].pgd;
	}

	/*
	 * After the lock is released, the original page table is restored.
	 */
	__flush_tlb_all();

	local_irq_restore(efi_rt_eflags);
}