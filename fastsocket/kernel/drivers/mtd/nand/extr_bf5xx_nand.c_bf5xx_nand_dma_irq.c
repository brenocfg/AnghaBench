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
struct bf5xx_nand_info {int /*<<< orphan*/  dma_completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_NFC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  clear_dma_irqstat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bf5xx_nand_dma_irq(int irq, void *dev_id)
{
	struct bf5xx_nand_info *info = dev_id;

	clear_dma_irqstat(CH_NFC);
	disable_dma(CH_NFC);
	complete(&info->dma_completion);

	return IRQ_HANDLED;
}