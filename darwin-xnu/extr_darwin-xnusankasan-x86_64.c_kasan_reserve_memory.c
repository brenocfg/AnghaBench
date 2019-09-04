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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ vm_address_t ;
typedef  scalar_t__ ppnum_t ;
struct TYPE_3__ {unsigned int MemoryMapDescriptorSize; unsigned int MemoryMapSize; scalar_t__ MemoryMap; scalar_t__ ksize; scalar_t__ kaddr; } ;
typedef  TYPE_1__ boot_args ;
struct TYPE_4__ {unsigned long NumberOfPages; int PhysicalStart; scalar_t__ Type; } ;
typedef  TYPE_2__ EfiMemoryRange ;

/* Variables and functions */
 unsigned long I386_PGBYTES ; 
 int I386_PGSHIFT ; 
 unsigned long STOLEN_MEM_BYTES ; 
 unsigned long STOLEN_MEM_PERCENT ; 
 int /*<<< orphan*/  alloc_superpage () ; 
 scalar_t__ kEfiConventionalMemory ; 
 void* kernel_vbase ; 
 void* kernel_vtop ; 
 void* ml_static_ptovirt (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned long shadow_pages_total ; 
 unsigned long shadow_pbase ; 
 unsigned long shadow_pnext ; 
 unsigned long shadow_ptop ; 
 unsigned int shadow_stolen_idx ; 
 int /*<<< orphan*/  zero_superpage_phys ; 

void
kasan_reserve_memory(void *_args)
{
	boot_args *args = (boot_args *)_args;
	vm_address_t pbase = args->kaddr;
	vm_address_t ptop = args->kaddr + args->ksize;

	kernel_vbase = ml_static_ptovirt(pbase);
	kernel_vtop = ml_static_ptovirt(ptop);

	EfiMemoryRange *mptr, *mptr_tmp;
	unsigned int mcount;
	unsigned int msize;
	unsigned int i;
	unsigned long total_pages;
	unsigned long to_steal;

	mptr = (EfiMemoryRange *)ml_static_ptovirt((vm_offset_t)args->MemoryMap);
	msize = args->MemoryMapDescriptorSize;
	mcount = args->MemoryMapSize / msize;

	/* sum total physical memory */
	total_pages = 0;
	for (i = 0, mptr_tmp = mptr; i < mcount; i++, mptr_tmp = (EfiMemoryRange *)(((vm_offset_t)mptr_tmp) + msize)) {
		total_pages += mptr_tmp->NumberOfPages;
	}

	to_steal = (total_pages * STOLEN_MEM_PERCENT) / 100 + (STOLEN_MEM_BYTES / I386_PGBYTES);

	/* Search for a range large enough to steal from */
	for (i = 0, mptr_tmp = mptr; i < mcount; i++, mptr_tmp = (EfiMemoryRange *)(((vm_offset_t)mptr_tmp) + msize)) {
		ppnum_t base, top;
		base = (ppnum_t)(mptr_tmp->PhysicalStart >> I386_PGSHIFT);
		top = (ppnum_t)((mptr_tmp->PhysicalStart >> I386_PGSHIFT) + mptr_tmp->NumberOfPages - 1);

		if ((mptr_tmp->Type == kEfiConventionalMemory) && (mptr_tmp->NumberOfPages > to_steal)) {
			/* Found a region with sufficient space - steal from the end */
			mptr_tmp->NumberOfPages -= to_steal;

			shadow_pbase = mptr_tmp->PhysicalStart + (mptr_tmp->NumberOfPages << I386_PGSHIFT);
			shadow_ptop = shadow_pbase + (to_steal << I386_PGSHIFT);
			shadow_pnext = shadow_pbase;
			shadow_pages_total = to_steal;
			shadow_stolen_idx = i;

			/* Set aside a page of zeros we can use for dummy shadow mappings */
			zero_superpage_phys = alloc_superpage();

			return;
		}
	}

	panic("KASAN: could not reserve memory");
}