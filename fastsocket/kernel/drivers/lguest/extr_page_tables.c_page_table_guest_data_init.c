#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lg_cpu {TYPE_2__* lg; } ;
struct TYPE_9__ {int /*<<< orphan*/  pgdir; int /*<<< orphan*/  reserve_mem; int /*<<< orphan*/  kernel_address; } ;
struct TYPE_8__ {TYPE_3__* kernel_address; TYPE_3__* lguest_data; TYPE_1__* pgdirs; } ;
struct TYPE_7__ {int gpgdir; } ;

/* Variables and functions */
 int RESERVE_MEM ; 
 scalar_t__ SWITCHER_PGD_INDEX ; 
 scalar_t__ SWITCHER_PMD_INDEX ; 
 scalar_t__ get_user (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*,TYPE_3__*) ; 
 scalar_t__ pgd_index (TYPE_3__*) ; 
 scalar_t__ pmd_index (TYPE_3__*) ; 
 scalar_t__ put_user (int,int /*<<< orphan*/ *) ; 

void page_table_guest_data_init(struct lg_cpu *cpu)
{
	/* We get the kernel address: above this is all kernel memory. */
	if (get_user(cpu->lg->kernel_address,
		&cpu->lg->lguest_data->kernel_address)
		/*
		 * We tell the Guest that it can't use the top 2 or 4 MB
		 * of virtual addresses used by the Switcher.
		 */
		|| put_user(RESERVE_MEM * 1024 * 1024,
			&cpu->lg->lguest_data->reserve_mem)
		|| put_user(cpu->lg->pgdirs[0].gpgdir,
			&cpu->lg->lguest_data->pgdir))
		kill_guest(cpu, "bad guest page %p", cpu->lg->lguest_data);

	/*
	 * In flush_user_mappings() we loop from 0 to
	 * "pgd_index(lg->kernel_address)".  This assumes it won't hit the
	 * Switcher mappings, so check that now.
	 */
#ifdef CONFIG_X86_PAE
	if (pgd_index(cpu->lg->kernel_address) == SWITCHER_PGD_INDEX &&
		pmd_index(cpu->lg->kernel_address) == SWITCHER_PMD_INDEX)
#else
	if (pgd_index(cpu->lg->kernel_address) >= SWITCHER_PGD_INDEX)
#endif
		kill_guest(cpu, "bad kernel address %#lx",
				 cpu->lg->kernel_address);
}