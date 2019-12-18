#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  unsigned long long mach_vm_offset_t ;
struct TYPE_8__ {scalar_t__ vmaddr; scalar_t__ vmsize; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_9__ {scalar_t__ min_offset; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ KEXT_ALLOC_BASE (unsigned long long) ; 
 scalar_t__ KEXT_ALLOC_SIZE (scalar_t__) ; 
 char* SEG_TEXT ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_FLAGS_FIXED ; 
 int VM_FLAGS_OVERWRITE ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE (scalar_t__) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_KEXT ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_2__*) ; 
 scalar_t__ VM_MAX_KERNEL_ADDRESS ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 TYPE_2__* g_kext_map ; 
 TYPE_1__* getsegbyname (char*) ; 
 TYPE_2__* kernel_map ; 
 scalar_t__ kext_alloc_base ; 
 scalar_t__ kext_alloc_max ; 
 void* kext_post_boot_base ; 
 scalar_t__ kmem_suballoc (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long long vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

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