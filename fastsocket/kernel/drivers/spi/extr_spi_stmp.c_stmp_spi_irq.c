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
struct stmp_spi {int /*<<< orphan*/  done; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmp3xxx_dma_clear_interrupt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stmp_spi_irq(int irq, void *dev_id)
{
	struct stmp_spi *ss = dev_id;

	stmp3xxx_dma_clear_interrupt(ss->dma);
	complete(&ss->done);
	return IRQ_HANDLED;
}