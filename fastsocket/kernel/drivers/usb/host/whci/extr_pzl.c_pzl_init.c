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
typedef  int /*<<< orphan*/  u64 ;
struct whc {scalar_t__ base; int /*<<< orphan*/  pz_list_dma; int /*<<< orphan*/ * pz_list; TYPE_1__* umc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QH_LINK_NTDS (int) ; 
 int QH_LINK_T ; 
 scalar_t__ WUSBPERIODICLISTBASE ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_writeq (int /*<<< orphan*/ ,scalar_t__) ; 

int pzl_init(struct whc *whc)
{
	int i;

	whc->pz_list = dma_alloc_coherent(&whc->umc->dev, sizeof(u64) * 16,
					  &whc->pz_list_dma, GFP_KERNEL);
	if (whc->pz_list == NULL)
		return -ENOMEM;

	/* Set T bit on all elements in PZL. */
	for (i = 0; i < 16; i++)
		whc->pz_list[i] = cpu_to_le64(QH_LINK_NTDS(8) | QH_LINK_T);

	le_writeq(whc->pz_list_dma, whc->base + WUSBPERIODICLISTBASE);

	return 0;
}