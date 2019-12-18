#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; int vm_flags; unsigned long vm_end; unsigned long vm_pgoff; TYPE_1__* vm_ops; scalar_t__ vm_file; int /*<<< orphan*/  anon_vma_chain; int /*<<< orphan*/  anon_vma; struct mm_struct* vm_mm; } ;
struct rb_node {int dummy; } ;
struct mm_struct {int dummy; } ;
struct mempolicy {int dummy; } ;
typedef  unsigned long pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* open ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 unsigned long PAGE_SHIFT ; 
 int VM_EXECUTABLE ; 
 int /*<<< orphan*/  added_exe_file_vma (struct mm_struct*) ; 
 scalar_t__ anon_vma_clone (struct vm_area_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  find_vma_prepare (struct mm_struct*,unsigned long,struct vm_area_struct**,struct rb_node***,struct rb_node**) ; 
 int /*<<< orphan*/  get_file (scalar_t__) ; 
 struct vm_area_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 struct mempolicy* mpol_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_area_cachep ; 
 int /*<<< orphan*/  vma_link (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,struct rb_node**,struct rb_node*) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ ,scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_set_policy (struct vm_area_struct*,struct mempolicy*) ; 

struct vm_area_struct *copy_vma(struct vm_area_struct **vmap,
	unsigned long addr, unsigned long len, pgoff_t pgoff)
{
	struct vm_area_struct *vma = *vmap;
	unsigned long vma_start = vma->vm_start;
	struct mm_struct *mm = vma->vm_mm;
	struct vm_area_struct *new_vma, *prev;
	struct rb_node **rb_link, *rb_parent;
	struct mempolicy *pol;

	/*
	 * If anonymous vma has not yet been faulted, update new pgoff
	 * to match new location, to increase its chance of merging.
	 */
	if (!vma->vm_file && !vma->anon_vma)
		pgoff = addr >> PAGE_SHIFT;

	find_vma_prepare(mm, addr, &prev, &rb_link, &rb_parent);
	new_vma = vma_merge(mm, prev, addr, addr + len, vma->vm_flags,
			vma->anon_vma, vma->vm_file, pgoff, vma_policy(vma));
	if (new_vma) {
		/*
		 * Source vma may have been merged into new_vma
		 */
		if (vma_start >= new_vma->vm_start &&
		    vma_start < new_vma->vm_end)
			*vmap = new_vma;
	} else {
		new_vma = kmem_cache_alloc(vm_area_cachep, GFP_KERNEL);
		if (new_vma) {
			*new_vma = *vma;
			pol = mpol_dup(vma_policy(vma));
			if (IS_ERR(pol))
				goto out_free_vma;
			INIT_LIST_HEAD(&new_vma->anon_vma_chain);
			if (anon_vma_clone(new_vma, vma))
				goto out_free_mempol;
			vma_set_policy(new_vma, pol);
			new_vma->vm_start = addr;
			new_vma->vm_end = addr + len;
			new_vma->vm_pgoff = pgoff;
			if (new_vma->vm_file) {
				get_file(new_vma->vm_file);
				if (vma->vm_flags & VM_EXECUTABLE)
					added_exe_file_vma(mm);
			}
			if (new_vma->vm_ops && new_vma->vm_ops->open)
				new_vma->vm_ops->open(new_vma);
			vma_link(mm, new_vma, prev, rb_link, rb_parent);
		}
	}
	return new_vma;

 out_free_mempol:
	mpol_put(pol);
 out_free_vma:
	kmem_cache_free(vm_area_cachep, new_vma);
	return NULL;
}