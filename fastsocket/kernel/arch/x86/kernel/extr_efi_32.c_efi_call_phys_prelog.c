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
struct desc_ptr {scalar_t__ size; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 scalar_t__ GDT_SIZE ; 
 int PAGE_OFFSET ; 
 unsigned long X86_CR4_PAE ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 TYPE_2__* efi_bak_pg_dir_pointer ; 
 int /*<<< orphan*/  efi_rt_eflags ; 
 int /*<<< orphan*/  get_cpu_gdt_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_gdt (struct desc_ptr*) ; 
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 
 size_t pgd_index (unsigned long) ; 
 unsigned long read_cr4_safe () ; 
 TYPE_1__* swapper_pg_dir ; 

void efi_call_phys_prelog(void)
{
	unsigned long cr4;
	unsigned long temp;
	struct desc_ptr gdt_descr;

	local_irq_save(efi_rt_eflags);

	/*
	 * If I don't have PAE, I should just duplicate two entries in page
	 * directory. If I have PAE, I just need to duplicate one entry in
	 * page directory.
	 */
	cr4 = read_cr4_safe();

	if (cr4 & X86_CR4_PAE) {
		efi_bak_pg_dir_pointer[0].pgd =
		    swapper_pg_dir[pgd_index(0)].pgd;
		swapper_pg_dir[0].pgd =
		    swapper_pg_dir[pgd_index(PAGE_OFFSET)].pgd;
	} else {
		efi_bak_pg_dir_pointer[0].pgd =
		    swapper_pg_dir[pgd_index(0)].pgd;
		efi_bak_pg_dir_pointer[1].pgd =
		    swapper_pg_dir[pgd_index(0x400000)].pgd;
		swapper_pg_dir[pgd_index(0)].pgd =
		    swapper_pg_dir[pgd_index(PAGE_OFFSET)].pgd;
		temp = PAGE_OFFSET + 0x400000;
		swapper_pg_dir[pgd_index(0x400000)].pgd =
		    swapper_pg_dir[pgd_index(temp)].pgd;
	}

	/*
	 * After the lock is released, the original page table is restored.
	 */
	__flush_tlb_all();

	gdt_descr.address = __pa(get_cpu_gdt_table(0));
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);
}