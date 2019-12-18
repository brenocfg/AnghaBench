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
struct ttm_placement {int dummy; } ;
struct ttm_mem_type_manager {int /*<<< orphan*/  priv; } ;
struct ttm_mem_reg {int num_pages; int start; struct nouveau_mem* mm_node; } ;
struct ttm_buffer_object {int dummy; } ;
struct nouveau_mem {int page_shift; TYPE_1__* vma; } ;
struct TYPE_2__ {int offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NV_MEM_ACCESS_RW ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  kfree (struct nouveau_mem*) ; 
 struct nouveau_mem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_vm_get (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
nv04_gart_manager_new(struct ttm_mem_type_manager *man,
		      struct ttm_buffer_object *bo,
		      struct ttm_placement *placement,
		      struct ttm_mem_reg *mem)
{
	struct nouveau_mem *node;
	int ret;

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	node->page_shift = 12;

	ret = nouveau_vm_get(man->priv, mem->num_pages << 12, node->page_shift,
			     NV_MEM_ACCESS_RW, &node->vma[0]);
	if (ret) {
		kfree(node);
		return ret;
	}

	mem->mm_node = node;
	mem->start   = node->vma[0].offset >> PAGE_SHIFT;
	return 0;
}