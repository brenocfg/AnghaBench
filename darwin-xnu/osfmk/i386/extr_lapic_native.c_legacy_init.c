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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  vm_map_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DFR ; 
 int KERN_SUCCESS ; 
 int LAPIC_DFR_FLAT ; 
 int LAPIC_LDR_SHIFT ; 
 int /*<<< orphan*/  LAPIC_SIZE ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LDR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IOKIT ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  VM_WIMG_IO ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_cpu_number () ; 
 scalar_t__ i386_btop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  lapic_pbase ; 
 scalar_t__ lapic_vbase ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int pmap_enter (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kernel () ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int vm_map_find_space (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
legacy_init(void)
{
	int		result;
	kern_return_t	kr;
	vm_map_entry_t	entry;
	vm_map_offset_t lapic_vbase64;
	/* Establish a map to the local apic */

	if (lapic_vbase == 0) {
		lapic_vbase64 = (vm_offset_t)vm_map_min(kernel_map);
		result = vm_map_find_space(kernel_map,
					   &lapic_vbase64,
					   round_page(LAPIC_SIZE), 0,
					   0,
					   VM_MAP_KERNEL_FLAGS_NONE,
					   VM_KERN_MEMORY_IOKIT,
					   &entry);
		/* Convert 64-bit vm_map_offset_t to "pointer sized" vm_offset_t
		 */
		lapic_vbase = (vm_offset_t) lapic_vbase64;
		if (result != KERN_SUCCESS) {
			panic("legacy_init: vm_map_find_entry FAILED (err=%d)", result);
		}
		vm_map_unlock(kernel_map);

		/*
		 * Map in the local APIC non-cacheable, as recommended by Intel
		 * in section 8.4.1 of the "System Programming Guide".
		 * In fact, this is redundant because EFI will have assigned an
		 * MTRR physical range containing the local APIC's MMIO space as
		 * UC and this will override the default PAT setting.
		 */
		kr = pmap_enter(pmap_kernel(),
		                lapic_vbase,
		                (ppnum_t) i386_btop(lapic_pbase),
		                VM_PROT_READ|VM_PROT_WRITE,
		                VM_PROT_NONE,
		                VM_WIMG_IO,
		                TRUE);

		assert(kr == KERN_SUCCESS);
	}

	/*
	 * Set flat delivery model, logical processor id
	 * This should already be the default set.
	 */
	LAPIC_WRITE(DFR, LAPIC_DFR_FLAT);
	LAPIC_WRITE(LDR, (get_cpu_number()) << LAPIC_LDR_SHIFT);
}