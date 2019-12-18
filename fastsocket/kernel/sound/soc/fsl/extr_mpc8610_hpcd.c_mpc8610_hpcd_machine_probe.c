#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct mpc8610_hpcd_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mpc8610_hpcd_data {int ssi_id; TYPE_2__* guts; int /*<<< orphan*/ * dma_channel_id; int /*<<< orphan*/  dma_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  pmuxcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCSR_GUTS_DMACR_DEV_SSI ; 
 int /*<<< orphan*/  CCSR_GUTS_PMUXCR_SSI1_MASK ; 
 int /*<<< orphan*/  CCSR_GUTS_PMUXCR_SSI1_SSI ; 
 int /*<<< orphan*/  CCSR_GUTS_PMUXCR_SSI2_MASK ; 
 int /*<<< orphan*/  CCSR_GUTS_PMUXCR_SSI2_SSI ; 
 int /*<<< orphan*/  clrsetbits_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guts_set_dmacr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guts_set_pmuxcr_dma (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc8610_hpcd_machine_probe(struct platform_device *sound_device)
{
	struct mpc8610_hpcd_data *machine_data =
		sound_device->dev.platform_data;

	/* Program the signal routing between the SSI and the DMA */
	guts_set_dmacr(machine_data->guts, machine_data->dma_id,
		machine_data->dma_channel_id[0], CCSR_GUTS_DMACR_DEV_SSI);
	guts_set_dmacr(machine_data->guts, machine_data->dma_id,
		machine_data->dma_channel_id[1], CCSR_GUTS_DMACR_DEV_SSI);

	guts_set_pmuxcr_dma(machine_data->guts, machine_data->dma_id,
		machine_data->dma_channel_id[0], 0);
	guts_set_pmuxcr_dma(machine_data->guts, machine_data->dma_id,
		machine_data->dma_channel_id[1], 0);

	switch (machine_data->ssi_id) {
	case 0:
		clrsetbits_be32(&machine_data->guts->pmuxcr,
			CCSR_GUTS_PMUXCR_SSI1_MASK, CCSR_GUTS_PMUXCR_SSI1_SSI);
		break;
	case 1:
		clrsetbits_be32(&machine_data->guts->pmuxcr,
			CCSR_GUTS_PMUXCR_SSI2_MASK, CCSR_GUTS_PMUXCR_SSI2_SSI);
		break;
	}

	return 0;
}