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
struct file {int f_flags; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int O_SYNC ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  X86_FEATURE_CENTAUR_MCR ; 
 int /*<<< orphan*/  X86_FEATURE_CYRIX_ARR ; 
 int /*<<< orphan*/  X86_FEATURE_K6_MTRR ; 
 int /*<<< orphan*/  X86_FEATURE_MTRR ; 
 unsigned long _PAGE_CACHE_MASK ; 
 unsigned long _PAGE_CACHE_UC ; 
 unsigned long _PAGE_CACHE_UC_MINUS ; 
 unsigned long _PAGE_CACHE_WB ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  high_memory ; 
 int /*<<< orphan*/  pat_enabled ; 
 unsigned long pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_is_allowed (unsigned long,unsigned long) ; 

int phys_mem_access_prot_allowed(struct file *file, unsigned long pfn,
				unsigned long size, pgprot_t *vma_prot)
{
	unsigned long flags = _PAGE_CACHE_WB;

	if (!range_is_allowed(pfn, size))
		return 0;

	if (file->f_flags & O_SYNC) {
		flags = _PAGE_CACHE_UC_MINUS;
	}

#ifdef CONFIG_X86_32
	/*
	 * On the PPro and successors, the MTRRs are used to set
	 * memory types for physical addresses outside main memory,
	 * so blindly setting UC or PWT on those pages is wrong.
	 * For Pentiums and earlier, the surround logic should disable
	 * caching for the high addresses through the KEN pin, but
	 * we maintain the tradition of paranoia in this code.
	 */
	if (!pat_enabled &&
	    !(boot_cpu_has(X86_FEATURE_MTRR) ||
	      boot_cpu_has(X86_FEATURE_K6_MTRR) ||
	      boot_cpu_has(X86_FEATURE_CYRIX_ARR) ||
	      boot_cpu_has(X86_FEATURE_CENTAUR_MCR)) &&
	    (pfn << PAGE_SHIFT) >= __pa(high_memory)) {
		flags = _PAGE_CACHE_UC;
	}
#endif

	*vma_prot = __pgprot((pgprot_val(*vma_prot) & ~_PAGE_CACHE_MASK) |
			     flags);
	return 1;
}