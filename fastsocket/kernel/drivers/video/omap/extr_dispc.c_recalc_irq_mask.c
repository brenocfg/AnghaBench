#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* irq_handlers; } ;
struct TYPE_3__ {unsigned long irq_mask; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQENABLE ; 
 unsigned long DISPC_IRQ_MASK_ERROR ; 
 int MAX_IRQ_HANDLERS ; 
 int /*<<< orphan*/  MOD_REG_FLD (int /*<<< orphan*/ ,int,unsigned long) ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 

__attribute__((used)) static void recalc_irq_mask(void)
{
	int i;
	unsigned long irq_mask = DISPC_IRQ_MASK_ERROR;

	for (i = 0; i < MAX_IRQ_HANDLERS; i++) {
		if (!dispc.irq_handlers[i].callback)
			continue;

		irq_mask |= dispc.irq_handlers[i].irq_mask;
	}

	enable_lcd_clocks(1);
	MOD_REG_FLD(DISPC_IRQENABLE, 0x7fff, irq_mask);
	enable_lcd_clocks(0);
}