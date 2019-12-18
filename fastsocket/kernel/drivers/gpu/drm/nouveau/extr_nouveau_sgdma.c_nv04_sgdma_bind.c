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
typedef  int u64 ;
struct ttm_tt {scalar_t__ sg; } ;
struct ttm_mem_reg {int num_pages; struct nouveau_mem* mm_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_address; } ;
struct nouveau_sgdma_be {struct nouveau_mem* node; TYPE_1__ ttm; } ;
struct nouveau_mem {int /*<<< orphan*/ * vma; int /*<<< orphan*/  pages; scalar_t__ sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_vm_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct nouveau_mem*) ; 
 int /*<<< orphan*/  nouveau_vm_map_sg_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct nouveau_mem*) ; 

__attribute__((used)) static int
nv04_sgdma_bind(struct ttm_tt *ttm, struct ttm_mem_reg *mem)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;
	struct nouveau_mem *node = mem->mm_node;
	u64 size = mem->num_pages << 12;

	if (ttm->sg) {
		node->sg = ttm->sg;
		nouveau_vm_map_sg_table(&node->vma[0], 0, size, node);
	} else {
		node->pages = nvbe->ttm.dma_address;
		nouveau_vm_map_sg(&node->vma[0], 0, size, node);
	}

	nvbe->node = node;
	return 0;
}