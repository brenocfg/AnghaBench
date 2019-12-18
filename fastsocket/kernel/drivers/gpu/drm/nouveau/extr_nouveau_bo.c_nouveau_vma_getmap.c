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
struct ttm_mem_reg {int num_pages; scalar_t__ mem_type; struct nouveau_mem* mm_node; } ;
struct nouveau_vma {int dummy; } ;
struct nouveau_mem {int /*<<< orphan*/  page_shift; } ;
struct nouveau_channel {int /*<<< orphan*/  cli; } ;
struct nouveau_bo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_MEM_ACCESS_RW ; 
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_VRAM ; 
 int nouveau_vm_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_vma*) ; 
 int /*<<< orphan*/  nouveau_vm_map (struct nouveau_vma*,struct nouveau_mem*) ; 
 int /*<<< orphan*/  nouveau_vm_map_sg (struct nouveau_vma*,int /*<<< orphan*/ ,int,struct nouveau_mem*) ; 
 TYPE_1__* nv_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_vma_getmap(struct nouveau_channel *chan, struct nouveau_bo *nvbo,
		   struct ttm_mem_reg *mem, struct nouveau_vma *vma)
{
	struct nouveau_mem *node = mem->mm_node;
	int ret;

	ret = nouveau_vm_get(nv_client(chan->cli)->vm, mem->num_pages <<
			     PAGE_SHIFT, node->page_shift,
			     NV_MEM_ACCESS_RW, vma);
	if (ret)
		return ret;

	if (mem->mem_type == TTM_PL_VRAM)
		nouveau_vm_map(vma, node);
	else
		nouveau_vm_map_sg(vma, 0, mem->num_pages << PAGE_SHIFT, node);

	return 0;
}