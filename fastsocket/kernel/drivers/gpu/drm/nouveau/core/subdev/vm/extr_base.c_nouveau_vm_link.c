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
struct nouveau_vmmgr {int /*<<< orphan*/  (* map_pgt ) (struct nouveau_gpuobj*,int,int /*<<< orphan*/ ) ;} ;
struct nouveau_vm_pgd {int /*<<< orphan*/  head; int /*<<< orphan*/  obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_vm {int fpde; int lpde; TYPE_2__ mm; int /*<<< orphan*/  pgd_list; TYPE_1__* pgt; struct nouveau_vmmgr* vmm; } ;
struct nouveau_gpuobj {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nouveau_vm_pgd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (struct nouveau_gpuobj*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_gpuobj*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_vm_link(struct nouveau_vm *vm, struct nouveau_gpuobj *pgd)
{
	struct nouveau_vmmgr *vmm = vm->vmm;
	struct nouveau_vm_pgd *vpgd;
	int i;

	if (!pgd)
		return 0;

	vpgd = kzalloc(sizeof(*vpgd), GFP_KERNEL);
	if (!vpgd)
		return -ENOMEM;

	nouveau_gpuobj_ref(pgd, &vpgd->obj);

	mutex_lock(&vm->mm.mutex);
	for (i = vm->fpde; i <= vm->lpde; i++)
		vmm->map_pgt(pgd, i, vm->pgt[i - vm->fpde].obj);
	list_add(&vpgd->head, &vm->pgd_list);
	mutex_unlock(&vm->mm.mutex);
	return 0;
}