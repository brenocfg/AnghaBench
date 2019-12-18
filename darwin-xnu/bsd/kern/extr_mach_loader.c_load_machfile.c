#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int vm_map_offset_t ;
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct vnode {int dummy; } ;
struct mach_header {int flags; } ;
struct image_params {scalar_t__ ip_arch_offset; scalar_t__ ip_arch_size; int ip_flags; scalar_t__ ip_new_thread; TYPE_1__* ip_vattr; struct vnode* ip_vp; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ load_return_t ;
struct TYPE_7__ {int is_64bit_addr; int is_64bit_data; scalar_t__ has_pagezero; } ;
typedef  TYPE_2__ load_result_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int int64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {scalar_t__ va_data_size; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FOURK_PAGE_SHIFT ; 
 int IMGPF_ALLOW_DATA_EXEC ; 
 int IMGPF_DISABLE_ASLR ; 
 int IMGPF_EXEC ; 
 int IMGPF_HIGH_BITS_ASLR ; 
 int IMGPF_IS_64BIT_ADDR ; 
 int IMGPF_IS_64BIT_DATA ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ LOAD_BADMACHO ; 
 scalar_t__ LOAD_FAILURE ; 
 scalar_t__ LOAD_SUCCESS ; 
 int MH_ALLOW_STACK_EXECUTION ; 
 int MH_NO_HEAP_EXECUTION ; 
 int MH_PIE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SIXTEENK_PAGE_SHIFT ; 
 scalar_t__ TRUE ; 
 int VM_MAP_HIGH_START_BITS_COUNT ; 
 int VM_MAP_HIGH_START_BITS_SHIFT ; 
 int /*<<< orphan*/  act_set_astbsd (scalar_t__) ; 
 int /*<<< orphan*/  cs_process_global_enforcement () ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  current_task () ; 
 scalar_t__ fourk_binary_compatibility_unsafe ; 
 int /*<<< orphan*/  get_task_ledger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (scalar_t__) ; 
 TYPE_2__ load_result_null ; 
 int /*<<< orphan*/  page_shift_user32 ; 
 scalar_t__ parse_machfile (struct vnode*,int /*<<< orphan*/ ,scalar_t__,struct mach_header*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ *,struct image_params*) ; 
 int /*<<< orphan*/  pmap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_transcommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int random () ; 
 int /*<<< orphan*/  task_complete_halt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_rollup_accounting_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_32bit_log_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_start_halt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_commit_pagezero_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_compute_max_offset (int) ; 
 int /*<<< orphan*/  vm_map_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_disable_NX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_disallow_data_exec (int /*<<< orphan*/ ) ; 
 int vm_map_get_max_aslr_slide_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_get_max_aslr_slide_section (int /*<<< orphan*/ ,int*,int*) ; 
 int vm_map_get_max_loader_aslr_slide_pages (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_has_hard_pagezero (int /*<<< orphan*/ ,int) ; 
 int vm_map_page_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_set_high_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_set_page_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_mark_exiting (int /*<<< orphan*/ ) ; 

load_return_t
load_machfile(
	struct image_params	*imgp,
	struct mach_header	*header,
	thread_t 		thread,
	vm_map_t 		*mapp,
	load_result_t		*result
)
{
	struct vnode		*vp = imgp->ip_vp;
	off_t			file_offset = imgp->ip_arch_offset;
	off_t			macho_size = imgp->ip_arch_size;
	off_t			file_size = imgp->ip_vattr->va_data_size;
	pmap_t			pmap = 0;	/* protected by create_map */
	vm_map_t		map;
	load_result_t		myresult;
	load_return_t		lret;
	boolean_t enforce_hard_pagezero = TRUE;
	int in_exec = (imgp->ip_flags & IMGPF_EXEC);
	task_t task = current_task();
	proc_t p = current_proc();
	int64_t			aslr_page_offset = 0;
	int64_t			dyld_aslr_page_offset = 0;
	int64_t			aslr_section_size = 0;
	int64_t			aslr_section_offset = 0;
	kern_return_t 		kret;

	if (macho_size > file_size) {
		return(LOAD_BADMACHO);
	}

	result->is_64bit_addr = ((imgp->ip_flags & IMGPF_IS_64BIT_ADDR) == IMGPF_IS_64BIT_ADDR);
	result->is_64bit_data = ((imgp->ip_flags & IMGPF_IS_64BIT_DATA) == IMGPF_IS_64BIT_DATA);

	task_t ledger_task;
	if (imgp->ip_new_thread) {
		ledger_task = get_threadtask(imgp->ip_new_thread);
	} else {
		ledger_task = task;
	}
	pmap = pmap_create(get_task_ledger(ledger_task),
			   (vm_map_size_t) 0,
			   result->is_64bit_addr);
	map = vm_map_create(pmap,
			0,
			vm_compute_max_offset(result->is_64bit_addr),
			TRUE);

#if defined(__arm64__)
	if (result->is_64bit_addr) {
		/* enforce 16KB alignment of VM map entries */
		vm_map_set_page_shift(map, SIXTEENK_PAGE_SHIFT);
	} else {
		vm_map_set_page_shift(map, page_shift_user32);
	}
#elif (__ARM_ARCH_7K__ >= 2) && defined(PLATFORM_WatchOS)
	/* enforce 16KB alignment for watch targets with new ABI */
	vm_map_set_page_shift(map, SIXTEENK_PAGE_SHIFT);
#endif /* __arm64__ */

#ifndef	CONFIG_ENFORCE_SIGNED_CODE
	/* This turns off faulting for executable pages, which allows
	 * to circumvent Code Signing Enforcement. The per process
	 * flag (CS_ENFORCEMENT) is not set yet, but we can use the
	 * global flag.
	 */
	if ( !cs_process_global_enforcement() && (header->flags & MH_ALLOW_STACK_EXECUTION) ) {
	        vm_map_disable_NX(map);
	        // TODO: Message Trace or log that this is happening
	}
#endif

	/* Forcibly disallow execution from data pages on even if the arch
	 * normally permits it. */
	if ((header->flags & MH_NO_HEAP_EXECUTION) && !(imgp->ip_flags & IMGPF_ALLOW_DATA_EXEC))
		vm_map_disallow_data_exec(map);

	/*
	 * Compute a random offset for ASLR, and an independent random offset for dyld.
	 */
	if (!(imgp->ip_flags & IMGPF_DISABLE_ASLR)) {
		vm_map_get_max_aslr_slide_section(map, &aslr_section_offset, &aslr_section_size);
		aslr_section_offset = (random() % aslr_section_offset) * aslr_section_size;

		aslr_page_offset = random();
		aslr_page_offset %= vm_map_get_max_aslr_slide_pages(map);
		aslr_page_offset <<= vm_map_page_shift(map);

		dyld_aslr_page_offset = random();
		dyld_aslr_page_offset %= vm_map_get_max_loader_aslr_slide_pages(map);
		dyld_aslr_page_offset <<= vm_map_page_shift(map);

		aslr_page_offset += aslr_section_offset;
	}

	if (!result)
		result = &myresult;

	*result = load_result_null;

	/*
	 * re-set the bitness on the load result since we cleared the load result above.
	 */
	result->is_64bit_addr = ((imgp->ip_flags & IMGPF_IS_64BIT_ADDR) == IMGPF_IS_64BIT_ADDR);
	result->is_64bit_data = ((imgp->ip_flags & IMGPF_IS_64BIT_DATA) == IMGPF_IS_64BIT_DATA);

	lret = parse_machfile(vp, map, thread, header, file_offset, macho_size,
	                      0, aslr_page_offset, dyld_aslr_page_offset, result,
			      NULL, imgp);

	if (lret != LOAD_SUCCESS) {
		vm_map_deallocate(map);	/* will lose pmap reference too */
		return(lret);
	}

#if __x86_64__
	/*
	 * On x86, for compatibility, don't enforce the hard page-zero restriction for 32-bit binaries.
	 */
	if (!result->is_64bit_addr) {
		enforce_hard_pagezero = FALSE;
	}

	/*
	 * For processes with IMGPF_HIGH_BITS_ASLR, add a few random high bits
	 * to the start address for "anywhere" memory allocations.
	 */
#define VM_MAP_HIGH_START_BITS_COUNT 8
#define VM_MAP_HIGH_START_BITS_SHIFT 27
	if (result->is_64bit_addr &&
	    (imgp->ip_flags & IMGPF_HIGH_BITS_ASLR)) {
		int random_bits;
		vm_map_offset_t high_start;

		random_bits = random();
		random_bits &= (1 << VM_MAP_HIGH_START_BITS_COUNT)-1;
		high_start = (((vm_map_offset_t)random_bits)
			      << VM_MAP_HIGH_START_BITS_SHIFT);
		vm_map_set_high_start(map, high_start);
	}
#endif /* __x86_64__ */

	/*
	 * Check to see if the page zero is enforced by the map->min_offset.
	 */ 
	if (enforce_hard_pagezero &&
	    (vm_map_has_hard_pagezero(map, 0x1000) == FALSE)) {
#if __arm64__
		if (!result->is_64bit_addr && /* not 64-bit address space */
		    !(header->flags & MH_PIE) &&	  /* not PIE */
		    (vm_map_page_shift(map) != FOURK_PAGE_SHIFT ||
		     PAGE_SHIFT != FOURK_PAGE_SHIFT) && /* page size != 4KB */
		    result->has_pagezero &&	/* has a "soft" page zero */
		    fourk_binary_compatibility_unsafe) {
			/*
			 * For backwards compatibility of "4K" apps on
			 * a 16K system, do not enforce a hard page zero...
			 */
		} else
#endif /* __arm64__ */
		{
			vm_map_deallocate(map);	/* will lose pmap reference too */
			return (LOAD_BADMACHO);
		}
	}

	vm_commit_pagezero_status(map);

	/*
	 * If this is an exec, then we are going to destroy the old
	 * task, and it's correct to halt it; if it's spawn, the
	 * task is not yet running, and it makes no sense.
	 */
	if (in_exec) {
		/*
		 * Mark the task as halting and start the other
		 * threads towards terminating themselves.  Then
		 * make sure any threads waiting for a process
		 * transition get informed that we are committed to
		 * this transition, and then finally complete the
		 * task halting (wait for threads and then cleanup
		 * task resources).
		 *
		 * NOTE: task_start_halt() makes sure that no new
		 * threads are created in the task during the transition.
		 * We need to mark the workqueue as exiting before we
		 * wait for threads to terminate (at the end of which
		 * we no longer have a prohibition on thread creation).
		 *
		 * Finally, clean up any lingering workqueue data structures
		 * that may have been left behind by the workqueue threads
		 * as they exited (and then clean up the work queue itself).
		 */
		kret = task_start_halt(task);
		if (kret != KERN_SUCCESS) {
			vm_map_deallocate(map);	/* will lose pmap reference too */
			return (LOAD_FAILURE);
		}
		proc_transcommit(p, 0);
		workq_mark_exiting(p);
		task_complete_halt(task);
		workq_exit(p);

		/*
		 * Roll up accounting info to new task. The roll up is done after
		 * task_complete_halt to make sure the thread accounting info is
		 * rolled up to current_task.
		 */
		task_rollup_accounting_info(get_threadtask(thread), task);
	}
	*mapp = map;

#ifdef CONFIG_32BIT_TELEMETRY
	if (!result->is_64bit_data) {
		/*
		 * This may not need to be an AST; we merely need to ensure that
		 * we gather telemetry at the point where all of the information
		 * that we want has been added to the process.
		 */
		task_set_32bit_log_flag(get_threadtask(thread));
		act_set_astbsd(thread);
	}
#endif /* CONFIG_32BIT_TELEMETRY */

	return(LOAD_SUCCESS);
}