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
 int /*<<< orphan*/  CH_EPPI0 ; 
 int EPPI_EN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int bfin_read_EPPI0_CONTROL () ; 
 scalar_t__ bfin_read_EPPI0_STATUS () ; 
 int /*<<< orphan*/  bfin_write_EPPI0_CONTROL (int) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_STATUS (int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bfin_bf54x_irq_error(int irq, void *dev_id)
{
	/*struct bfin_bf54xfb_info *info = dev_id;*/

	u16 status = bfin_read_EPPI0_STATUS();

	bfin_write_EPPI0_STATUS(0xFFFF);

	if (status) {
		bfin_write_EPPI0_CONTROL(bfin_read_EPPI0_CONTROL() & ~EPPI_EN);
		disable_dma(CH_EPPI0);

		/* start dma */
		enable_dma(CH_EPPI0);
		bfin_write_EPPI0_CONTROL(bfin_read_EPPI0_CONTROL() | EPPI_EN);
		bfin_write_EPPI0_STATUS(0xFFFF);
	}

	return IRQ_HANDLED;
}