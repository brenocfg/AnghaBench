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
struct vm_area_struct {unsigned int vm_flags; TYPE_1__* vm_file; int /*<<< orphan*/  vm_page_prot; TYPE_2__* vm_ops; } ;
struct TYPE_4__ {scalar_t__ page_mkwrite; } ;
struct TYPE_3__ {scalar_t__ f_mapping; } ;

/* Variables and functions */
 unsigned int VM_INSERTPAGE ; 
 unsigned int VM_PFNMAP ; 
 unsigned int VM_SHARED ; 
 unsigned int VM_WRITE ; 
 scalar_t__ mapping_cap_account_dirty (scalar_t__) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_page_prot (unsigned int) ; 

int vma_wants_writenotify(struct vm_area_struct *vma)
{
	unsigned int vm_flags = vma->vm_flags;

	/* If it was private or non-writable, the write bit is already clear */
	if ((vm_flags & (VM_WRITE|VM_SHARED)) != ((VM_WRITE|VM_SHARED)))
		return 0;

	/* The backer wishes to know when pages are first written to? */
	if (vma->vm_ops && vma->vm_ops->page_mkwrite)
		return 1;

	/* The open routine did something to the protections already? */
	if (pgprot_val(vma->vm_page_prot) !=
	    pgprot_val(vm_get_page_prot(vm_flags)))
		return 0;

	/* Specialty mapping? */
	if (vm_flags & (VM_PFNMAP|VM_INSERTPAGE))
		return 0;

	/* Can the mapping track the dirty pages? */
	return vma->vm_file && vma->vm_file->f_mapping &&
		mapping_cap_account_dirty(vma->vm_file->f_mapping);
}