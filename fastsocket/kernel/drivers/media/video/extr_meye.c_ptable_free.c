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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {scalar_t__ mchip_dmahandle; int /*<<< orphan*/ * mchip_ptable_toc; int /*<<< orphan*/ ** mchip_ptable; TYPE_1__* mchip_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MCHIP_NB_PAGES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ meye ; 

__attribute__((used)) static void ptable_free(void)
{
	u32 *pt;
	int i;

	pt = meye.mchip_ptable_toc;
	for (i = 0; i < MCHIP_NB_PAGES; i++) {
		dma_addr_t dma = (dma_addr_t) *pt;
		if (meye.mchip_ptable[i])
			dma_free_coherent(&meye.mchip_dev->dev,
					  PAGE_SIZE,
					  meye.mchip_ptable[i], dma);
		pt++;
	}

	if (meye.mchip_ptable_toc)
		dma_free_coherent(&meye.mchip_dev->dev,
				  PAGE_SIZE,
				  meye.mchip_ptable_toc,
				  meye.mchip_dmahandle);

	memset(meye.mchip_ptable, 0, sizeof(meye.mchip_ptable));
	meye.mchip_ptable_toc = NULL;
	meye.mchip_dmahandle = 0;
}