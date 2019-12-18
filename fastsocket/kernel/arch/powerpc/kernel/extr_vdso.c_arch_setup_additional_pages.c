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
struct page {int dummy; } ;
struct TYPE_3__ {unsigned long vdso_base; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; TYPE_1__ context; } ;
struct linux_binprm {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 unsigned long VDSO32_MBASE ; 
 int VDSO_ALIGNMENT ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 int VM_READ ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned long get_unmapped_area (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int install_special_mapping (struct mm_struct*,unsigned long,unsigned long,int,struct page**) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct page** vdso32_pagelist ; 
 unsigned long vdso32_pages ; 
 struct page** vdso64_pagelist ; 
 unsigned long vdso64_pages ; 
 int /*<<< orphan*/  vdso_ready ; 

int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
{
	struct mm_struct *mm = current->mm;
	struct page **vdso_pagelist;
	unsigned long vdso_pages;
	unsigned long vdso_base;
	int rc;

	if (!vdso_ready)
		return 0;

#ifdef CONFIG_PPC64
	if (test_thread_flag(TIF_32BIT)) {
		vdso_pagelist = vdso32_pagelist;
		vdso_pages = vdso32_pages;
		vdso_base = VDSO32_MBASE;
	} else {
		vdso_pagelist = vdso64_pagelist;
		vdso_pages = vdso64_pages;
		/*
		 * On 64bit we don't have a preferred map address. This
		 * allows get_unmapped_area to find an area near other mmaps
		 * and most likely share a SLB entry.
		 */
		vdso_base = 0;
	}
#else
	vdso_pagelist = vdso32_pagelist;
	vdso_pages = vdso32_pages;
	vdso_base = VDSO32_MBASE;
#endif

	current->mm->context.vdso_base = 0;

	/* vDSO has a problem and was disabled, just don't "enable" it for the
	 * process
	 */
	if (vdso_pages == 0)
		return 0;
	/* Add a page to the vdso size for the data page */
	vdso_pages ++;

	/*
	 * pick a base address for the vDSO in process space. We try to put it
	 * at vdso_base which is the "natural" base for it, but we might fail
	 * and end up putting it elsewhere.
	 * Add enough to the size so that the result can be aligned.
	 */
	down_write(&mm->mmap_sem);
	vdso_base = get_unmapped_area(NULL, vdso_base,
				      (vdso_pages << PAGE_SHIFT) +
				      ((VDSO_ALIGNMENT - 1) & PAGE_MASK),
				      0, 0);
	if (IS_ERR_VALUE(vdso_base)) {
		rc = vdso_base;
		goto fail_mmapsem;
	}

	/* Add required alignment. */
	vdso_base = ALIGN(vdso_base, VDSO_ALIGNMENT);

	/*
	 * Put vDSO base into mm struct. We need to do this before calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO (since arch_vma_name fails).
	 */
	current->mm->context.vdso_base = vdso_base;

	/*
	 * our vma flags don't have VM_WRITE so by default, the process isn't
	 * allowed to write those pages.
	 * gdb can break that with ptrace interface, and thus trigger COW on
	 * those pages but it's then your responsibility to never do that on
	 * the "data" page of the vDSO or you'll stop getting kernel updates
	 * and your nice userland gettimeofday will be totally dead.
	 * It's fine to use that for setting breakpoints in the vDSO code
	 * pages though.
	 */
	rc = install_special_mapping(mm, vdso_base, vdso_pages << PAGE_SHIFT,
				     VM_READ|VM_EXEC|
				     VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				     vdso_pagelist);
	if (rc) {
		current->mm->context.vdso_base = 0;
		goto fail_mmapsem;
	}

	up_write(&mm->mmap_sem);
	return 0;

 fail_mmapsem:
	up_write(&mm->mmap_sem);
	return rc;
}