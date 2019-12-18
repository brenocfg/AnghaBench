#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {unsigned long pgoff; scalar_t__ virtual_address; } ;
struct vm_area_struct {int vm_start; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_mm; TYPE_1__* vm_file; } ;
struct spu_state {int use_big_pages; TYPE_2__* lscsa; } ;
struct spu_context {scalar_t__ state; TYPE_3__* spu; struct spu_state csa; } ;
struct TYPE_6__ {unsigned long local_store_phys; } ;
struct TYPE_5__ {scalar_t__ ls; } ;
struct TYPE_4__ {struct spu_context* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long LS_SIZE ; 
 int MMU_PAGE_64K ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_SIGBUS ; 
 int get_slice_psize (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pgprot_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached_wc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 scalar_t__ spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  vm_insert_pfn (struct vm_area_struct*,unsigned long,unsigned long) ; 
 unsigned long vmalloc_to_pfn (scalar_t__) ; 

__attribute__((used)) static int
spufs_mem_mmap_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct spu_context *ctx	= vma->vm_file->private_data;
	unsigned long address = (unsigned long)vmf->virtual_address;
	unsigned long pfn, offset;

#ifdef CONFIG_SPU_FS_64K_LS
	struct spu_state *csa = &ctx->csa;
	int psize;

	/* Check what page size we are using */
	psize = get_slice_psize(vma->vm_mm, address);

	/* Some sanity checking */
	BUG_ON(csa->use_big_pages != (psize == MMU_PAGE_64K));

	/* Wow, 64K, cool, we need to align the address though */
	if (csa->use_big_pages) {
		BUG_ON(vma->vm_start & 0xffff);
		address &= ~0xfffful;
	}
#endif /* CONFIG_SPU_FS_64K_LS */

	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset >= LS_SIZE)
		return VM_FAULT_SIGBUS;

	pr_debug("spufs_mem_mmap_fault address=0x%lx, offset=0x%lx\n",
			address, offset);

	if (spu_acquire(ctx))
		return VM_FAULT_NOPAGE;

	if (ctx->state == SPU_STATE_SAVED) {
		vma->vm_page_prot = pgprot_cached(vma->vm_page_prot);
		pfn = vmalloc_to_pfn(ctx->csa.lscsa->ls + offset);
	} else {
		vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);
		pfn = (ctx->spu->local_store_phys + offset) >> PAGE_SHIFT;
	}
	vm_insert_pfn(vma, address, pfn);

	spu_release(ctx);

	return VM_FAULT_NOPAGE;
}