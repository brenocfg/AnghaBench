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
typedef  int /*<<< orphan*/  u32 ;
struct bcma_device {TYPE_1__* bus; } ;
struct TYPE_2__ {int hosttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_DMA_TRANSLATION_DMA32_CMT ; 
 int /*<<< orphan*/  BCMA_DMA_TRANSLATION_DMA64_CMT ; 
 int /*<<< orphan*/  BCMA_DMA_TRANSLATION_NONE ; 
#define  BCMA_HOSTTYPE_PCI 129 
#define  BCMA_HOSTTYPE_SOC 128 
 int /*<<< orphan*/  BCMA_IOST ; 
 int BCMA_IOST_DMA64 ; 
 int bcma_aread32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_err (TYPE_1__*,char*,int) ; 

u32 bcma_core_dma_translation(struct bcma_device *core)
{
	switch (core->bus->hosttype) {
	case BCMA_HOSTTYPE_SOC:
		return 0;
	case BCMA_HOSTTYPE_PCI:
		if (bcma_aread32(core, BCMA_IOST) & BCMA_IOST_DMA64)
			return BCMA_DMA_TRANSLATION_DMA64_CMT;
		else
			return BCMA_DMA_TRANSLATION_DMA32_CMT;
	default:
		bcma_err(core->bus, "DMA translation unknown for host %d\n",
			 core->bus->hosttype);
	}
	return BCMA_DMA_TRANSLATION_NONE;
}