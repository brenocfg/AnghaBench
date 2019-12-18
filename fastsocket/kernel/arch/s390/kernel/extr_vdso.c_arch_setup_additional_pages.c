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
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 int VM_READ ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned long get_unmapped_area (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int install_special_mapping (struct mm_struct*,unsigned long,unsigned long,int,struct page**) ; 
 scalar_t__ is_compat_task () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct page** vdso32_pagelist ; 
 unsigned long vdso32_pages ; 
 struct page** vdso64_pagelist ; 
 unsigned long vdso64_pages ; 
 int /*<<< orphan*/  vdso_enabled ; 

int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
{
	struct mm_struct *mm = current->mm;
	struct page **vdso_pagelist;
	unsigned long vdso_pages;
	unsigned long vdso_base;
	int rc;

	if (!vdso_enabled)
		return 0;
	/*
	 * Only map the vdso for dynamically linked elf binaries.
	 */
	if (!uses_interp)
		return 0;

#ifdef CONFIG_64BIT
	vdso_pagelist = vdso64_pagelist;
	vdso_pages = vdso64_pages;
#ifdef CONFIG_COMPAT
	if (is_compat_task()) {
		vdso_pagelist = vdso32_pagelist;
		vdso_pages = vdso32_pages;
	}
#endif
#else
	vdso_pagelist = vdso32_pagelist;
	vdso_pages = vdso32_pages;
#endif

	/*
	 * vDSO has a problem and was disabled, just don't "enable" it for
	 * the process
	 */
	if (vdso_pages == 0)
		return 0;

	current->mm->context.vdso_base = 0;

	/*
	 * pick a base address for the vDSO in process space. We try to put
	 * it at vdso_base which is the "natural" base for it, but we might
	 * fail and end up putting it elsewhere.
	 */
	down_write(&mm->mmap_sem);
	vdso_base = get_unmapped_area(NULL, 0, vdso_pages << PAGE_SHIFT, 0, 0);
	if (IS_ERR_VALUE(vdso_base)) {
		rc = vdso_base;
		goto out_up;
	}

	/*
	 * Put vDSO base into mm struct. We need to do this before calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO (since arch_vma_name fails).
	 */
	current->mm->context.vdso_base = vdso_base;

	/*
	 * our vma flags don't have VM_WRITE so by default, the process
	 * isn't allowed to write those pages.
	 * gdb can break that with ptrace interface, and thus trigger COW
	 * on those pages but it's then your responsibility to never do that
	 * on the "data" page of the vDSO or you'll stop getting kernel
	 * updates and your nice userland gettimeofday will be totally dead.
	 * It's fine to use that for setting breakpoints in the vDSO code
	 * pages though.
	 */
	rc = install_special_mapping(mm, vdso_base, vdso_pages << PAGE_SHIFT,
				     VM_READ|VM_EXEC|
				     VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				     vdso_pagelist);
	if (rc)
		current->mm->context.vdso_base = 0;
out_up:
	up_write(&mm->mmap_sem);
	return rc;
}