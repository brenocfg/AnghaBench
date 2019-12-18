#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bf5xx_nand_info {int /*<<< orphan*/  device; int /*<<< orphan*/  dma_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_NFC ; 
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  bf5xx_nand_dma_irq ; 
 int bfin_read_DMAC1_PERIMUX () ; 
 int /*<<< orphan*/  bfin_write_DMAC1_PERIMUX (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardware_ecc ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int request_dma (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_dma_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bf5xx_nand_info*) ; 

__attribute__((used)) static int bf5xx_nand_dma_init(struct bf5xx_nand_info *info)
{
	int ret;

	/* Do not use dma */
	if (!hardware_ecc)
		return 0;

	init_completion(&info->dma_completion);

	/* Request NFC DMA channel */
	ret = request_dma(CH_NFC, "BF5XX NFC driver");
	if (ret < 0) {
		dev_err(info->device, " unable to get DMA channel\n");
		return ret;
	}

#ifdef CONFIG_BF54x
	/* Setup DMAC1 channel mux for NFC which shared with SDH */
	bfin_write_DMAC1_PERIMUX(bfin_read_DMAC1_PERIMUX() & ~1);
	SSYNC();
#endif

	set_dma_callback(CH_NFC, bf5xx_nand_dma_irq, info);

	/* Turn off the DMA channel first */
	disable_dma(CH_NFC);
	return 0;
}