#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  size_t uint32_t ;
typedef  int ppnum_t ;
struct TYPE_9__ {size_t list_size; size_t page_count; size_t bank_count; TYPE_2__* bank_bitmap; } ;
typedef  TYPE_1__ hibernate_page_list_t ;
struct TYPE_10__ {int first_page; int last_page; int bitmapwords; int /*<<< orphan*/ * bitmap; } ;
typedef  TYPE_2__ hibernate_bitmap_t ;
struct TYPE_11__ {scalar_t__ MemoryMapDescriptorSize; size_t MemoryMapSize; int /*<<< orphan*/  MemoryMap; } ;
typedef  TYPE_3__ boot_args ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {scalar_t__ bootArgs; } ;
struct TYPE_12__ {int PhysicalStart; int Type; scalar_t__ NumberOfPages; } ;
typedef  TYPE_4__ EfiMemoryRange ;

/* Variables and functions */
 int I386_PGSHIFT ; 
 int MAX_BANKS ; 
 TYPE_8__ PE_state ; 
 int atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,TYPE_2__*,int) ; 
#define  kEfiACPIMemoryNVS 141 
#define  kEfiACPIReclaimMemory 140 
#define  kEfiBootServicesCode 139 
#define  kEfiBootServicesData 138 
#define  kEfiConventionalMemory 137 
#define  kEfiLoaderCode 136 
#define  kEfiLoaderData 135 
#define  kEfiMemoryMappedIO 134 
#define  kEfiMemoryMappedIOPortSpace 133 
#define  kEfiPalCode 132 
#define  kEfiReservedMemoryType 131 
#define  kEfiRuntimeServicesCode 130 
#define  kEfiRuntimeServicesData 129 
#define  kEfiUnusableMemory 128 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kprintf (char*,size_t,int,int) ; 
 int max_ppnum ; 
 scalar_t__ ml_static_ptovirt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 scalar_t__ shadow_pages_total ; 
 int /*<<< orphan*/  shadow_ptop ; 
 size_t shadow_stolen_idx ; 

hibernate_page_list_t *
hibernate_page_list_allocate(boolean_t log)
{
    ppnum_t		    base, num;
    vm_size_t               size;
    uint32_t                bank, num_banks;
    uint32_t		    pages, page_count;
    hibernate_page_list_t * list;
    hibernate_bitmap_t *    bitmap;

    EfiMemoryRange *	    mptr;
    uint32_t		    mcount, msize, i;
    hibernate_bitmap_t	    dram_ranges[MAX_BANKS];
    boot_args *		    args = (boot_args *) PE_state.bootArgs;
    uint32_t		    non_os_pagecount;
    ppnum_t		    pnmax = max_ppnum;

    mptr = (EfiMemoryRange *)ml_static_ptovirt(args->MemoryMap);
    if (args->MemoryMapDescriptorSize == 0)
	panic("Invalid memory map descriptor size");
    msize = args->MemoryMapDescriptorSize;
    mcount = args->MemoryMapSize / msize;

#if KASAN
    /* adjust max page number to include stolen memory */
    if (atop(shadow_ptop) > pnmax) {
	pnmax = (ppnum_t)atop(shadow_ptop);
    }
#endif

    num_banks = 0;
    non_os_pagecount = 0;
    for (i = 0; i < mcount; i++, mptr = (EfiMemoryRange *)(((vm_offset_t)mptr) + msize))
    {
	base = (ppnum_t) (mptr->PhysicalStart >> I386_PGSHIFT);
	num = (ppnum_t) mptr->NumberOfPages;

#if KASAN
	if (i == shadow_stolen_idx) {
	    /*
	     * Add all stolen pages to the bitmap. Later we will prune the unused
	     * pages.
	     */
	    num += shadow_pages_total;
	}
#endif

	if (base > pnmax)
		continue;
	if ((base + num - 1) > pnmax)
		num = pnmax - base + 1;
	if (!num)
		continue;

	switch (mptr->Type)
	{
	    // any kind of dram
	    case kEfiACPIMemoryNVS:
	    case kEfiPalCode:
		non_os_pagecount += num;

	    // OS used dram
	    case kEfiLoaderCode:
	    case kEfiLoaderData:
	    case kEfiBootServicesCode:
	    case kEfiBootServicesData:
	    case kEfiConventionalMemory:

		for (bank = 0; bank < num_banks; bank++)
		{
		    if (dram_ranges[bank].first_page <= base)
			continue;
		    if ((base + num) == dram_ranges[bank].first_page)
		    {
			dram_ranges[bank].first_page = base;
			num = 0;
		    }
		    break;
		}
		if (!num) break;
		
		if (bank && (base == (1 + dram_ranges[bank - 1].last_page)))
		    bank--;
		else
		{
		    num_banks++;
		    if (num_banks >= MAX_BANKS) break;
		    bcopy(&dram_ranges[bank], 
			  &dram_ranges[bank + 1], 
			  (num_banks - bank - 1) * sizeof(hibernate_bitmap_t));
		    dram_ranges[bank].first_page = base;
		}
		dram_ranges[bank].last_page = base + num - 1;
		break;

	    // runtime services will be restarted, so no save
	    case kEfiRuntimeServicesCode:
	    case kEfiRuntimeServicesData:
	    // contents are volatile once the platform expert starts
	    case kEfiACPIReclaimMemory:
	    // non dram
	    case kEfiReservedMemoryType:
	    case kEfiUnusableMemory:
	    case kEfiMemoryMappedIO:
	    case kEfiMemoryMappedIOPortSpace:
	    default:
		break;
	}
    }

    if (num_banks >= MAX_BANKS)
	return (NULL);

    // size the hibernation bitmap

    size = sizeof(hibernate_page_list_t);
    page_count = 0;
    for (bank = 0; bank < num_banks; bank++) {
	pages = dram_ranges[bank].last_page + 1 - dram_ranges[bank].first_page;
	page_count += pages;
        size += sizeof(hibernate_bitmap_t) + ((pages + 31) >> 5) * sizeof(uint32_t);
    }

    list = (hibernate_page_list_t *)kalloc(size);
    if (!list)
	return (list);
	
    list->list_size  = (uint32_t)size;
    list->page_count = page_count;
    list->bank_count = num_banks;

    // convert to hibernation bitmap.

    bitmap = &list->bank_bitmap[0];
    for (bank = 0; bank < num_banks; bank++)
    {
        bitmap->first_page = dram_ranges[bank].first_page;
        bitmap->last_page  = dram_ranges[bank].last_page;
        bitmap->bitmapwords = (bitmap->last_page + 1
                               - bitmap->first_page + 31) >> 5;
        if (log) kprintf("hib bank[%d]: 0x%x000 end 0x%xfff\n",
        		  bank, bitmap->first_page, bitmap->last_page);
	bitmap = (hibernate_bitmap_t *) &bitmap->bitmap[bitmap->bitmapwords];
    }
    if (log) printf("efi pagecount %d\n", non_os_pagecount);

    return (list);
}