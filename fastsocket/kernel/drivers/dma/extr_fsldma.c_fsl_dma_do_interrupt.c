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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_dma_device {int feature; scalar_t__* chan; int /*<<< orphan*/  reg_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FSL_DMA_BIG_ENDIAN ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_dma_chan_do_interrupt (int,scalar_t__) ; 
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fsl_dma_do_interrupt(int irq, void *data)
{
	struct fsl_dma_device *fdev = (struct fsl_dma_device *)data;
	u32 gsr;
	int ch_nr;

	gsr = (fdev->feature & FSL_DMA_BIG_ENDIAN) ? in_be32(fdev->reg_base)
			: in_le32(fdev->reg_base);
	ch_nr = (32 - ffs(gsr)) / 8;

	return fdev->chan[ch_nr] ? fsl_dma_chan_do_interrupt(irq,
			fdev->chan[ch_nr]) : IRQ_NONE;
}