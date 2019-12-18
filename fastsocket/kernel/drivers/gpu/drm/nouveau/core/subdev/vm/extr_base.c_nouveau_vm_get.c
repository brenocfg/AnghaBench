#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nouveau_vmmgr {int pgt_bits; scalar_t__ spg_shift; } ;
struct nouveau_vma {int offset; int access; TYPE_2__* node; struct nouveau_vm* vm; } ;
struct nouveau_vm_pgt {int /*<<< orphan*/ * refcount; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_vm {TYPE_1__ mm; int /*<<< orphan*/  fpde; struct nouveau_vm_pgt* pgt; struct nouveau_vmmgr* vmm; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_mm_free (TYPE_1__*,TYPE_2__**) ; 
 int nouveau_mm_head (TYPE_1__*,int,int,int,int,TYPE_2__**) ; 
 int nouveau_vm_map_pgt (struct nouveau_vm*,int,scalar_t__) ; 
 int /*<<< orphan*/  nouveau_vm_unmap_pgt (struct nouveau_vm*,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

int
nouveau_vm_get(struct nouveau_vm *vm, u64 size, u32 page_shift,
	       u32 access, struct nouveau_vma *vma)
{
	struct nouveau_vmmgr *vmm = vm->vmm;
	u32 align = (1 << page_shift) >> 12;
	u32 msize = size >> 12;
	u32 fpde, lpde, pde;
	int ret;

	mutex_lock(&vm->mm.mutex);
	ret = nouveau_mm_head(&vm->mm, page_shift, msize, msize, align,
			     &vma->node);
	if (unlikely(ret != 0)) {
		mutex_unlock(&vm->mm.mutex);
		return ret;
	}

	fpde = (vma->node->offset >> vmm->pgt_bits);
	lpde = (vma->node->offset + vma->node->length - 1) >> vmm->pgt_bits;

	for (pde = fpde; pde <= lpde; pde++) {
		struct nouveau_vm_pgt *vpgt = &vm->pgt[pde - vm->fpde];
		int big = (vma->node->type != vmm->spg_shift);

		if (likely(vpgt->refcount[big])) {
			vpgt->refcount[big]++;
			continue;
		}

		ret = nouveau_vm_map_pgt(vm, pde, vma->node->type);
		if (ret) {
			if (pde != fpde)
				nouveau_vm_unmap_pgt(vm, big, fpde, pde - 1);
			nouveau_mm_free(&vm->mm, &vma->node);
			mutex_unlock(&vm->mm.mutex);
			return ret;
		}
	}
	mutex_unlock(&vm->mm.mutex);

	vma->vm     = vm;
	vma->offset = (u64)vma->node->offset << 12;
	vma->access = access;
	return 0;
}