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
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PPI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bfin_read_PPI_STATUS () ; 
 int /*<<< orphan*/  bfin_t350mcqb_disable_ppi () ; 
 int /*<<< orphan*/  bfin_t350mcqb_enable_ppi () ; 
 int /*<<< orphan*/  bfin_write_PPI_STATUS (int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bfin_t350mcqb_irq_error(int irq, void *dev_id)
{
	/*struct bfin_t350mcqbfb_info *info = (struct bfin_t350mcqbfb_info *)dev_id;*/

	u16 status = bfin_read_PPI_STATUS();
	bfin_write_PPI_STATUS(0xFFFF);

	if (status) {
		bfin_t350mcqb_disable_ppi();
		disable_dma(CH_PPI);

		/* start dma */
		enable_dma(CH_PPI);
		bfin_t350mcqb_enable_ppi();
		bfin_write_PPI_STATUS(0xFFFF);
	}

	return IRQ_HANDLED;
}