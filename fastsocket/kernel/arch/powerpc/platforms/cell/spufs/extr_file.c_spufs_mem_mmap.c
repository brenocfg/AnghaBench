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
struct vm_area_struct {int vm_start; int vm_pgoff; int vm_flags; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_end; } ;
struct spu_state {scalar_t__ use_big_pages; } ;
struct spu_context {struct spu_state csa; } ;
struct file {struct spu_context* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  pgprot_noncached_wc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spufs_mem_mmap_vmops ; 

__attribute__((used)) static int spufs_mem_mmap(struct file *file, struct vm_area_struct *vma)
{
#ifdef CONFIG_SPU_FS_64K_LS
	struct spu_context	*ctx = file->private_data;
	struct spu_state	*csa = &ctx->csa;

	/* Sanity check VMA alignment */
	if (csa->use_big_pages) {
		pr_debug("spufs_mem_mmap 64K, start=0x%lx, end=0x%lx,"
			 " pgoff=0x%lx\n", vma->vm_start, vma->vm_end,
			 vma->vm_pgoff);
		if (vma->vm_start & 0xffff)
			return -EINVAL;
		if (vma->vm_pgoff & 0xf)
			return -EINVAL;
	}
#endif /* CONFIG_SPU_FS_64K_LS */

	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);

	vma->vm_ops = &spufs_mem_mmap_vmops;
	return 0;
}