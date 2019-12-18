#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvc0_fifo_base {TYPE_1__* pgd; int /*<<< orphan*/  vm; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int NVOBJ_FLAG_HEAP ; 
 int NVOBJ_FLAG_ZERO_ALLOC ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 TYPE_3__* nouveau_client (struct nouveau_object*) ; 
 int nouveau_fifo_context_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ *,int,int,int,struct nvc0_fifo_base**) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int nouveau_vm_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct nouveau_object* nv_object (struct nvc0_fifo_base*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nvc0_fifo_base*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvc0_fifo_context_ctor(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, void *data, u32 size,
		       struct nouveau_object **pobject)
{
	struct nvc0_fifo_base *base;
	int ret;

	ret = nouveau_fifo_context_create(parent, engine, oclass, NULL, 0x1000,
				          0x1000, NVOBJ_FLAG_ZERO_ALLOC |
					  NVOBJ_FLAG_HEAP, &base);
	*pobject = nv_object(base);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_new(parent, NULL, 0x10000, 0x1000, 0, &base->pgd);
	if (ret)
		return ret;

	nv_wo32(base, 0x0200, lower_32_bits(base->pgd->addr));
	nv_wo32(base, 0x0204, upper_32_bits(base->pgd->addr));
	nv_wo32(base, 0x0208, 0xffffffff);
	nv_wo32(base, 0x020c, 0x000000ff);

	ret = nouveau_vm_ref(nouveau_client(parent)->vm, &base->vm, base->pgd);
	if (ret)
		return ret;

	return 0;
}