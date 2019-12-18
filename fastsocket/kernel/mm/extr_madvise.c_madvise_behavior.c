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
struct vm_area_struct {unsigned long vm_flags; unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  anon_vma; scalar_t__ vm_pgoff; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  MADV_DODUMP 138 
#define  MADV_DOFORK 137 
#define  MADV_DONTDUMP 136 
#define  MADV_DONTFORK 135 
#define  MADV_HUGEPAGE 134 
#define  MADV_MERGEABLE 133 
#define  MADV_NOHUGEPAGE 132 
#define  MADV_NORMAL 131 
#define  MADV_RANDOM 130 
#define  MADV_SEQUENTIAL 129 
#define  MADV_UNMERGEABLE 128 
 unsigned long PAGE_SHIFT ; 
 unsigned long VM_DONTCOPY ; 
 int VM_IO ; 
 unsigned long VM_NODUMP ; 
 unsigned long VM_RAND_READ ; 
 unsigned long VM_SEQ_READ ; 
 int hugepage_madvise (unsigned long*,int) ; 
 int ksm_madvise (struct vm_area_struct*,unsigned long,unsigned long,int,unsigned long*) ; 
 int split_vma (struct mm_struct*,struct vm_area_struct*,unsigned long,int) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

__attribute__((used)) static long madvise_behavior(struct vm_area_struct * vma,
		     struct vm_area_struct **prev,
		     unsigned long start, unsigned long end, int behavior)
{
	struct mm_struct * mm = vma->vm_mm;
	int error = 0;
	pgoff_t pgoff;
	unsigned long new_flags = vma->vm_flags;

	switch (behavior) {
	case MADV_NORMAL:
		new_flags = new_flags & ~VM_RAND_READ & ~VM_SEQ_READ;
		break;
	case MADV_SEQUENTIAL:
		new_flags = (new_flags & ~VM_RAND_READ) | VM_SEQ_READ;
		break;
	case MADV_RANDOM:
		new_flags = (new_flags & ~VM_SEQ_READ) | VM_RAND_READ;
		break;
	case MADV_DONTFORK:
		new_flags |= VM_DONTCOPY;
		break;
	case MADV_DOFORK:
		if (vma->vm_flags & VM_IO) {
			error = -EINVAL;
			goto out;
		}
		new_flags &= ~VM_DONTCOPY;
		break;
	case MADV_DONTDUMP:
		new_flags |= VM_NODUMP;
		break;
	case MADV_DODUMP:
		new_flags &= ~VM_NODUMP;
		break;
	case MADV_MERGEABLE:
	case MADV_UNMERGEABLE:
		error = ksm_madvise(vma, start, end, behavior, &new_flags);
		if (error)
			goto out;
		break;
	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
		error = hugepage_madvise(&new_flags, behavior);
		if (error)
			goto out;
		break;
	}

	if (new_flags == vma->vm_flags) {
		*prev = vma;
		goto out;
	}

	pgoff = vma->vm_pgoff + ((start - vma->vm_start) >> PAGE_SHIFT);
	*prev = vma_merge(mm, *prev, start, end, new_flags, vma->anon_vma,
				vma->vm_file, pgoff, vma_policy(vma));
	if (*prev) {
		vma = *prev;
		goto success;
	}

	*prev = vma;

	if (start != vma->vm_start) {
		error = split_vma(mm, vma, start, 1);
		if (error)
			goto out;
	}

	if (end != vma->vm_end) {
		error = split_vma(mm, vma, end, 0);
		if (error)
			goto out;
	}

success:
	/*
	 * vm_flags is protected by the mmap_sem held in write mode.
	 */
	vma->vm_flags = new_flags;

out:
	if (error == -ENOMEM)
		error = -EAGAIN;
	return error;
}