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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ BONITO_IRQ_BASE ; 
 int /*<<< orphan*/  bonito_irq_type ; 
 int /*<<< orphan*/  dma_timeout_irqaction ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_irq (scalar_t__,int /*<<< orphan*/ *) ; 

void bonito_irq_init(void)
{
	u32 i;

	for (i = BONITO_IRQ_BASE; i < BONITO_IRQ_BASE + 32; i++)
		set_irq_chip_and_handler(i, &bonito_irq_type, handle_level_irq);

	setup_irq(BONITO_IRQ_BASE + 10, &dma_timeout_irqaction);
}