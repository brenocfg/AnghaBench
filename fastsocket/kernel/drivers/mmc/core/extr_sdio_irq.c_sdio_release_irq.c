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
struct sdio_func {int num; int /*<<< orphan*/  card; int /*<<< orphan*/ * irq_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SDIO_CCCR_IENx ; 
 int mmc_io_rw_direct (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_card_irq_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 

int sdio_release_irq(struct sdio_func *func)
{
	int ret;
	unsigned char reg;

	BUG_ON(!func);
	BUG_ON(!func->card);

	pr_debug("SDIO: Disabling IRQ for %s...\n", sdio_func_id(func));

	if (func->irq_handler) {
		func->irq_handler = NULL;
		sdio_card_irq_put(func->card);
	}

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IENx, 0, &reg);
	if (ret)
		return ret;

	reg &= ~(1 << func->num);

	/* Disable master interrupt with the last function interrupt */
	if (!(reg & 0xFE))
		reg = 0;

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IENx, reg, NULL);
	if (ret)
		return ret;

	return 0;
}