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
typedef  int u32 ;
struct nouveau_vmmgr {int pgt_bits; scalar_t__ spg_shift; } ;
struct nouveau_vma {TYPE_2__* node; struct nouveau_vm* vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_vm {TYPE_1__ mm; struct nouveau_vmmgr* vmm; } ;
struct TYPE_4__ {int offset; int length; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_mm_free (TYPE_1__*,TYPE_2__**) ; 
 int /*<<< orphan*/  nouveau_vm_unmap_pgt (struct nouveau_vm*,int,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void
nouveau_vm_put(struct nouveau_vma *vma)
{
	struct nouveau_vm *vm = vma->vm;
	struct nouveau_vmmgr *vmm = vm->vmm;
	u32 fpde, lpde;

	if (unlikely(vma->node == NULL))
		return;
	fpde = (vma->node->offset >> vmm->pgt_bits);
	lpde = (vma->node->offset + vma->node->length - 1) >> vmm->pgt_bits;

	mutex_lock(&vm->mm.mutex);
	nouveau_vm_unmap_pgt(vm, vma->node->type != vmm->spg_shift, fpde, lpde);
	nouveau_mm_free(&vm->mm, &vma->node);
	mutex_unlock(&vm->mm.mutex);
}