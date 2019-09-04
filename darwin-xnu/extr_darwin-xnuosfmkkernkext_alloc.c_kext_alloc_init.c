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
 int /*<<< orphan*/  VM_MAX_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  g_kext_map ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kext_alloc_base ; 
 int /*<<< orphan*/  kext_alloc_max ; 

void 
kext_alloc_init(void)
{
#if CONFIG_KEXT_BASEMENT
    kern_return_t rval = 0;
    kernel_segment_command_t *text = NULL;
    kernel_segment_command_t *prelinkTextSegment = NULL;
    mach_vm_offset_t text_end, text_start;
    mach_vm_size_t text_size;
    mach_vm_size_t kext_alloc_size;

    /* Determine the start of the kernel's __TEXT segment and determine the
     * lower bound of the allocated submap for kext allocations.
     */

    text = getsegbyname(SEG_TEXT);
    text_start = vm_map_trunc_page(text->vmaddr,
				   VM_MAP_PAGE_MASK(kernel_map));
    text_start &= ~((512ULL * 1024 * 1024 * 1024) - 1);
    text_end = vm_map_round_page(text->vmaddr + text->vmsize,
				 VM_MAP_PAGE_MASK(kernel_map));
    text_size = text_end - text_start;

    kext_alloc_base = KEXT_ALLOC_BASE(text_end);
    kext_alloc_size = KEXT_ALLOC_SIZE(text_size);
    kext_alloc_max = kext_alloc_base + kext_alloc_size;
    
    /* Post boot kext allocation will start after the prelinked kexts */
    prelinkTextSegment = getsegbyname("__PRELINK_TEXT");
    if (prelinkTextSegment) {
        /* use kext_post_boot_base to start allocations past all the prelinked 
         * kexts
         */
        kext_post_boot_base = 
		vm_map_round_page(kext_alloc_base + prelinkTextSegment->vmsize,
				  VM_MAP_PAGE_MASK(kernel_map));
    }
    else {
        kext_post_boot_base = kext_alloc_base;
    }

    /* Allocate the sub block of the kernel map */
    rval = kmem_suballoc(kernel_map, (vm_offset_t *) &kext_alloc_base, 
			 kext_alloc_size, /* pageable */ TRUE,
			 VM_FLAGS_FIXED|VM_FLAGS_OVERWRITE,
			 VM_MAP_KERNEL_FLAGS_NONE, VM_KERN_MEMORY_KEXT,
			 &g_kext_map);
    if (rval != KERN_SUCCESS) {
	    panic("kext_alloc_init: kmem_suballoc failed 0x%x\n", rval);
    }

    if ((kext_alloc_base + kext_alloc_size) > kext_alloc_max) {
        panic("kext_alloc_init: failed to get first 2GB\n");
    }

    if (kernel_map->min_offset > kext_alloc_base) {
	    kernel_map->min_offset = kext_alloc_base;
    }

    printf("kext submap [0x%lx - 0x%lx], kernel text [0x%lx - 0x%lx]\n",
	   VM_KERNEL_UNSLIDE(kext_alloc_base),
	   VM_KERNEL_UNSLIDE(kext_alloc_max),
	   VM_KERNEL_UNSLIDE(text->vmaddr),
	   VM_KERNEL_UNSLIDE(text->vmaddr + text->vmsize));

#else
    g_kext_map = kernel_map;
    kext_alloc_base = VM_MIN_KERNEL_ADDRESS;
    kext_alloc_max = VM_MAX_KERNEL_ADDRESS;
#endif /* CONFIG_KEXT_BASEMENT */
}