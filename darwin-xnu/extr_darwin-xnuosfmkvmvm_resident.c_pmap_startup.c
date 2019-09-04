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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  fillval ;
typedef  int addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PE_parse_boot_argn (char*,unsigned int*,int) ; 
 int /*<<< orphan*/  VM_CHECK_MEMORYSTATUS ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PAGE_PACK_PTR (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_PAGE_UNPACK_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillPage (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kernel_debug_string_early (char*) ; 
 int /*<<< orphan*/  kprintf (char*,unsigned int) ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 scalar_t__ pmap_free_pages () ; 
 int /*<<< orphan*/  pmap_next_page (scalar_t__*) ; 
 scalar_t__ pmap_steal_memory (unsigned int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ virtual_space_end ; 
 scalar_t__ virtual_space_start ; 
 int vm_himemory_mode ; 
 int /*<<< orphan*/ * vm_page_array_beginning_addr ; 
 int /*<<< orphan*/ * vm_page_array_boundary ; 
 int /*<<< orphan*/ * vm_page_array_ending_addr ; 
 int /*<<< orphan*/  vm_page_init (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_lowest ; 
 int /*<<< orphan*/  vm_page_pages ; 
 int /*<<< orphan*/  vm_page_release_startup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_pages ; 
 int vm_pages_count ; 

void
pmap_startup(
	vm_offset_t *startp,
	vm_offset_t *endp)
{
	unsigned int i, npages, pages_initialized, fill, fillval;
	ppnum_t		phys_page;
	addr64_t	tmpaddr;

#if    defined(__LP64__)
	/*
	 * make sure we are aligned on a 64 byte boundary
	 * for VM_PAGE_PACK_PTR (it clips off the low-order
	 * 6 bits of the pointer)
	 */
	if (virtual_space_start != virtual_space_end)
		virtual_space_start = round_page(virtual_space_start);
#endif

	/*
	 *	We calculate how many page frames we will have
	 *	and then allocate the page structures in one chunk.
	 */

	tmpaddr = (addr64_t)pmap_free_pages() * (addr64_t)PAGE_SIZE;	/* Get the amount of memory left */
	tmpaddr = tmpaddr + (addr64_t)(round_page(virtual_space_start) - virtual_space_start);	/* Account for any slop */
	npages = (unsigned int)(tmpaddr / (addr64_t)(PAGE_SIZE + sizeof(*vm_pages)));	/* Figure size of all vm_page_ts, including enough to hold the vm_page_ts */

	vm_pages = (vm_page_t) pmap_steal_memory(npages * sizeof *vm_pages);

	/*
	 *	Initialize the page frames.
	 */
	kernel_debug_string_early("Initialize the page frames");

	vm_page_array_beginning_addr = &vm_pages[0];
	vm_page_array_ending_addr = &vm_pages[npages];

	for (i = 0, pages_initialized = 0; i < npages; i++) {
		if (!pmap_next_page(&phys_page))
			break;
#if defined(__arm__) || defined(__arm64__)
		if (pages_initialized == 0) {
			vm_first_phys_ppnum = phys_page;
			patch_low_glo_vm_page_info((void *)vm_page_array_beginning_addr, (void *)vm_page_array_ending_addr, vm_first_phys_ppnum);
		}
		assert((i + vm_first_phys_ppnum) == phys_page);
#endif
		if (pages_initialized == 0 || phys_page < vm_page_lowest)
			vm_page_lowest = phys_page;

		vm_page_init(&vm_pages[i], phys_page, FALSE);
		vm_page_pages++;
		pages_initialized++;
	}
	vm_pages_count = pages_initialized;
	vm_page_array_boundary = &vm_pages[pages_initialized];

#if    defined(__LP64__)

	if ((vm_page_t)(VM_PAGE_UNPACK_PTR(VM_PAGE_PACK_PTR(&vm_pages[0]))) != &vm_pages[0])
		panic("VM_PAGE_PACK_PTR failed on &vm_pages[0] - %p", (void *)&vm_pages[0]);

	if ((vm_page_t)(VM_PAGE_UNPACK_PTR(VM_PAGE_PACK_PTR(&vm_pages[vm_pages_count-1]))) != &vm_pages[vm_pages_count-1])
		panic("VM_PAGE_PACK_PTR failed on &vm_pages[vm_pages_count-1] - %p", (void *)&vm_pages[vm_pages_count-1]);
#endif
	kernel_debug_string_early("page fill/release");
	/*
	 * Check if we want to initialize pages to a known value
	 */
	fill = 0;								/* Assume no fill */
	if (PE_parse_boot_argn("fill", &fillval, sizeof (fillval))) fill = 1;			/* Set fill */
#if	DEBUG
	/* This slows down booting the DEBUG kernel, particularly on
	 * large memory systems, but is worthwhile in deterministically
	 * trapping uninitialized memory usage.
	 */
	if (fill == 0) {
		fill = 1;
		fillval = 0xDEB8F177;
	}
#endif
	if (fill)
		kprintf("Filling vm_pages with pattern: 0x%x\n", fillval);

#if CONFIG_SECLUDED_MEMORY
	/* default: no secluded mem */
	secluded_mem_mb = 0;
	if (max_mem > 1*1024*1024*1024) {
		/* default to 90MB for devices with > 1GB of RAM */
		secluded_mem_mb = 90;
	}
	/* override with value from device tree, if provided */
	PE_get_default("kern.secluded_mem_mb",
		       &secluded_mem_mb, sizeof(secluded_mem_mb));
	/* override with value from boot-args, if provided */
	PE_parse_boot_argn("secluded_mem_mb",
			   &secluded_mem_mb,
			   sizeof (secluded_mem_mb));

	vm_page_secluded_target = (unsigned int)
		((secluded_mem_mb * 1024ULL * 1024ULL) / PAGE_SIZE);
	PE_parse_boot_argn("secluded_for_iokit",
			   &secluded_for_iokit,
			   sizeof (secluded_for_iokit));
	PE_parse_boot_argn("secluded_for_apps",
			   &secluded_for_apps,
			   sizeof (secluded_for_apps));
	PE_parse_boot_argn("secluded_for_filecache",
			   &secluded_for_filecache,
			   sizeof (secluded_for_filecache));
#if 11
	PE_parse_boot_argn("secluded_for_fbdp",
			   &secluded_for_fbdp,
			   sizeof (secluded_for_fbdp));
#endif

	/*
	 * On small devices, allow a large app to effectively suppress
	 * secluded memory until it exits.
	 */
	if (max_mem <= 1 * 1024 * 1024 * 1024 && vm_page_secluded_target != 0) {

		/*
		 * Get an amount from boot-args, else use 500MB.
		 * 500MB was chosen from a Peace daemon tentpole test which used munch
		 * to induce jetsam thrashing of false idle daemons.
		 */
		int secluded_shutoff_mb;
		if (PE_parse_boot_argn("secluded_shutoff_mb", &secluded_shutoff_mb,
		    sizeof (secluded_shutoff_mb)))
			secluded_shutoff_trigger = (uint64_t)secluded_shutoff_mb * 1024 * 1024;
		else
			secluded_shutoff_trigger = 500 * 1024 * 1024;

		if (secluded_shutoff_trigger != 0)
			secluded_suppression_init();
	}

#endif /* CONFIG_SECLUDED_MEMORY */

	/*
	 * By default release pages in reverse order so that physical pages
	 * initially get allocated in ascending addresses. This keeps
	 * the devices (which must address physical memory) happy if
	 * they require several consecutive pages.
	 *
	 * For debugging, you can reverse this ordering and/or fill
	 * all pages with a known value.
	 */
	if (vm_himemory_mode == 2) {
		for (i = 0; i < pages_initialized; i++) {
			if (fill)
				fillPage(VM_PAGE_GET_PHYS_PAGE(&vm_pages[i]), fillval);
			vm_page_release_startup(&vm_pages[i]);
		}
	} else {
		for (i = pages_initialized; i-- > 0; ) {
			if (fill)
				fillPage(VM_PAGE_GET_PHYS_PAGE(&vm_pages[i]), fillval);
			vm_page_release_startup(&vm_pages[i]);
		}
	}

	VM_CHECK_MEMORYSTATUS;
	
#if 0
	{
		vm_page_t xx, xxo, xxl;
		int i, j, k, l;
	
		j = 0;													/* (BRINGUP) */
		xxl = 0;
		
		for( i = 0; i < vm_colors; i++ ) {
			queue_iterate(&vm_page_queue_free[i].qhead,
				      xx,
				      vm_page_t,
				      vmp_pageq) {	/* BRINGUP */
				j++;												/* (BRINGUP) */
				if(j > vm_page_free_count) {						/* (BRINGUP) */
					panic("pmap_startup: too many pages, xx = %08X, xxl = %08X\n", xx, xxl);
				}
				
				l = vm_page_free_count - j;							/* (BRINGUP) */
				k = 0;												/* (BRINGUP) */
				
				if(((j - 1) & 0xFFFF) == 0) kprintf("checking number %d of %d\n", j, vm_page_free_count);

				for(xxo = xx->pageq.next; xxo != &vm_page_queue_free[i].qhead; xxo = xxo->pageq.next) {	/* (BRINGUP) */
					k++;
					if(k > l) panic("pmap_startup: too many in secondary check %d %d\n", k, l);
					if((xx->phys_page & 0xFFFFFFFF) == (xxo->phys_page & 0xFFFFFFFF)) {	/* (BRINGUP) */
						panic("pmap_startup: duplicate physaddr, xx = %08X, xxo = %08X\n", xx, xxo);
					}
				}

				xxl = xx;
			}
		}
		
		if(j != vm_page_free_count) {						/* (BRINGUP) */
			panic("pmap_startup: vm_page_free_count does not match, calc =  %d, vm_page_free_count = %08X\n", j, vm_page_free_count);
		}
	}
#endif


	/*
	 *	We have to re-align virtual_space_start,
	 *	because pmap_steal_memory has been using it.
	 */

	virtual_space_start = round_page(virtual_space_start);

	*startp = virtual_space_start;
	*endp = virtual_space_end;
}