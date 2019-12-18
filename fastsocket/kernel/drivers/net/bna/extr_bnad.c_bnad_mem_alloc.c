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
struct bnad {TYPE_1__* pcidev; } ;
struct bna_mem_info {int num; scalar_t__ len; scalar_t__ mem_type; TYPE_2__* mdl; } ;
struct bna_mem_descr {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * kva; int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNA_MEM_T_DMA ; 
 int /*<<< orphan*/  BNA_SET_DMA_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bnad_mem_free (struct bnad*,struct bna_mem_info*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnad_mem_alloc(struct bnad *bnad,
	       struct bna_mem_info *mem_info)
{
	int i;
	dma_addr_t dma_pa;

	if ((mem_info->num == 0) || (mem_info->len == 0)) {
		mem_info->mdl = NULL;
		return 0;
	}

	mem_info->mdl = kcalloc(mem_info->num, sizeof(struct bna_mem_descr),
				GFP_KERNEL);
	if (mem_info->mdl == NULL)
		return -ENOMEM;

	if (mem_info->mem_type == BNA_MEM_T_DMA) {
		for (i = 0; i < mem_info->num; i++) {
			mem_info->mdl[i].len = mem_info->len;
			mem_info->mdl[i].kva =
				dma_alloc_coherent(&bnad->pcidev->dev,
						   mem_info->len, &dma_pa,
						   GFP_KERNEL);
			if (mem_info->mdl[i].kva == NULL)
				goto err_return;

			BNA_SET_DMA_ADDR(dma_pa,
					 &(mem_info->mdl[i].dma));
		}
	} else {
		for (i = 0; i < mem_info->num; i++) {
			mem_info->mdl[i].len = mem_info->len;
			mem_info->mdl[i].kva = kzalloc(mem_info->len,
							GFP_KERNEL);
			if (mem_info->mdl[i].kva == NULL)
				goto err_return;
		}
	}

	return 0;

err_return:
	bnad_mem_free(bnad, mem_info);
	return -ENOMEM;
}