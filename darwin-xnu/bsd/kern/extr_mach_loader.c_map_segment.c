#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
struct TYPE_7__ {void* vmkf_cs_enforcement_override; void* vmkf_cs_enforcement; void* vmkf_fourk; } ;
typedef  TYPE_1__ vm_map_kernel_flags_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ memory_object_control_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
struct TYPE_8__ {int csflags; } ;
typedef  TYPE_2__ load_result_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int CS_ENFORCEMENT ; 
 void* FALSE ; 
 int /*<<< orphan*/  IPC_PORT_NULL ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ LOAD_BADMACHO ; 
 scalar_t__ LOAD_NOSPACE ; 
 scalar_t__ LOAD_SUCCESS ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_FIXED ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 TYPE_1__ VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_enter_mem_object (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_enter_mem_object_control (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_page_aligned (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_page_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,scalar_t__) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,scalar_t__) ; 

__attribute__((used)) static kern_return_t
map_segment(
	vm_map_t		map,
	vm_map_offset_t		vm_start,
	vm_map_offset_t		vm_end,
	memory_object_control_t	control,
	vm_map_offset_t		file_start,
	vm_map_offset_t		file_end,
	vm_prot_t		initprot,
	vm_prot_t		maxprot,
	load_result_t		*result)
{
	vm_map_offset_t	cur_offset, cur_start, cur_end;
	kern_return_t	ret;
	vm_map_offset_t	effective_page_mask;
	vm_map_kernel_flags_t vmk_flags, cur_vmk_flags;
	
	if (vm_end < vm_start ||
	    file_end < file_start) {
		return LOAD_BADMACHO;
	}
	if (vm_end == vm_start ||
	    file_end == file_start) {
		/* nothing to map... */
		return LOAD_SUCCESS;
	}

	effective_page_mask = MAX(PAGE_MASK, vm_map_page_mask(map));

	vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
	if (vm_map_page_aligned(vm_start, effective_page_mask) &&
	    vm_map_page_aligned(vm_end, effective_page_mask) &&
	    vm_map_page_aligned(file_start, effective_page_mask) &&
	    vm_map_page_aligned(file_end, effective_page_mask)) {
		/* all page-aligned and map-aligned: proceed */
	} else {
#if __arm64__
		/* use an intermediate "4K" pager */
		vmk_flags.vmkf_fourk = TRUE;
#else /* __arm64__ */
		panic("map_segment: unexpected mis-alignment "
		      "vm[0x%llx:0x%llx] file[0x%llx:0x%llx]\n",
		      (uint64_t) vm_start,
		      (uint64_t) vm_end,
		      (uint64_t) file_start,
		      (uint64_t) file_end);
#endif /* __arm64__ */
	}

	cur_offset = 0;
	cur_start = vm_start;
	cur_end = vm_start;
#if __arm64__
	if (!vm_map_page_aligned(vm_start, effective_page_mask)) {
		/* one 4K pager for the 1st page */
		cur_end = vm_map_round_page(cur_start, effective_page_mask);
		if (cur_end > vm_end) {
			cur_end = vm_start + (file_end - file_start);
		}
		if (control != MEMORY_OBJECT_CONTROL_NULL) {
			ret = vm_map_enter_mem_object_control(
				map,
				&cur_start,
				cur_end - cur_start,
				(mach_vm_offset_t)0,
				VM_FLAGS_FIXED,
				vmk_flags,
				VM_KERN_MEMORY_NONE,
				control,
				file_start + cur_offset,
				TRUE, /* copy */
				initprot, maxprot,
				VM_INHERIT_DEFAULT);
		} else {
			ret = vm_map_enter_mem_object(
				map,
				&cur_start,
				cur_end - cur_start,
				(mach_vm_offset_t)0,
				VM_FLAGS_FIXED,
				vmk_flags,
				VM_KERN_MEMORY_NONE,
				IPC_PORT_NULL,
				0, /* offset */
				TRUE, /* copy */
				initprot, maxprot,
				VM_INHERIT_DEFAULT);
		}
		if (ret != KERN_SUCCESS) {
			return (LOAD_NOSPACE);
		}
		cur_offset += cur_end - cur_start;
	}
#endif /* __arm64__ */
	if (cur_end >= vm_start + (file_end - file_start)) {
		/* all mapped: done */
		goto done;
	}
	if (vm_map_round_page(cur_end, effective_page_mask) >=
	    vm_map_trunc_page(vm_start + (file_end - file_start),
			      effective_page_mask)) {
		/* no middle */
	} else {
		cur_start = cur_end;
		if ((vm_start & effective_page_mask) !=
		    (file_start & effective_page_mask)) {
			/* one 4K pager for the middle */
			cur_vmk_flags = vmk_flags;
		} else {
			/* regular mapping for the middle */
			cur_vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
		}

#if CONFIG_EMBEDDED
		(void) result;
#else /* CONFIG_EMBEDDED */
		/*
		 * This process doesn't have its new csflags (from
		 * the image being loaded) yet, so tell VM to override the
		 * current process's CS_ENFORCEMENT for this mapping.
		 */
		if (result->csflags & CS_ENFORCEMENT) {
			cur_vmk_flags.vmkf_cs_enforcement = TRUE;
		} else {
			cur_vmk_flags.vmkf_cs_enforcement = FALSE;
		}
		cur_vmk_flags.vmkf_cs_enforcement_override = TRUE;
#endif /* CONFIG_EMBEDDED */

		cur_end = vm_map_trunc_page(vm_start + (file_end -
							file_start),
					    effective_page_mask);
		if (control != MEMORY_OBJECT_CONTROL_NULL) {
			ret = vm_map_enter_mem_object_control(
				map,
				&cur_start,
				cur_end - cur_start,
				(mach_vm_offset_t)0,
				VM_FLAGS_FIXED,
				cur_vmk_flags,
				VM_KERN_MEMORY_NONE,
				control,
				file_start + cur_offset,
				TRUE, /* copy */
				initprot, maxprot,
				VM_INHERIT_DEFAULT);
		} else {
			ret = vm_map_enter_mem_object(
				map,
				&cur_start,
				cur_end - cur_start,
				(mach_vm_offset_t)0,
				VM_FLAGS_FIXED,
				cur_vmk_flags,
				VM_KERN_MEMORY_NONE,
				IPC_PORT_NULL,
				0, /* offset */
				TRUE, /* copy */
				initprot, maxprot,
				VM_INHERIT_DEFAULT);
		}
		if (ret != KERN_SUCCESS) {
			return (LOAD_NOSPACE);
		}
		cur_offset += cur_end - cur_start;
	}
	if (cur_end >= vm_start + (file_end - file_start)) {
		/* all mapped: done */
		goto done;
	}
	cur_start = cur_end;
#if __arm64__
	if (!vm_map_page_aligned(vm_start + (file_end - file_start),
				 effective_page_mask)) {
		/* one 4K pager for the last page */
		cur_end = vm_start + (file_end - file_start);
		if (control != MEMORY_OBJECT_CONTROL_NULL) {
			ret = vm_map_enter_mem_object_control(
				map,
				&cur_start,
				cur_end - cur_start,
				(mach_vm_offset_t)0,
				VM_FLAGS_FIXED,
				vmk_flags,
				VM_KERN_MEMORY_NONE,
				control,
				file_start + cur_offset,
				TRUE, /* copy */
				initprot, maxprot,
				VM_INHERIT_DEFAULT);
		} else {
			ret = vm_map_enter_mem_object(
				map,
				&cur_start,
				cur_end - cur_start,
				(mach_vm_offset_t)0,
				VM_FLAGS_FIXED,
				vmk_flags,
				VM_KERN_MEMORY_NONE,
				IPC_PORT_NULL,
				0, /* offset */
				TRUE, /* copy */
				initprot, maxprot,
				VM_INHERIT_DEFAULT);
		}
		if (ret != KERN_SUCCESS) {
			return (LOAD_NOSPACE);
		}
		cur_offset += cur_end - cur_start;
	}
#endif /* __arm64__ */
done:
	assert(cur_end >= vm_start + (file_end - file_start));
	return LOAD_SUCCESS;
}