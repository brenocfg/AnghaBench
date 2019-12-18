#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ vsync_dma_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  omap_enable_lcd_dma () ; 
 TYPE_1__ sossi ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t sossi_match_irq(int irq, void *data)
{
	unsigned long flags;

	spin_lock_irqsave(&sossi.lock, flags);
	if (sossi.vsync_dma_pending) {
		sossi.vsync_dma_pending--;
		omap_enable_lcd_dma();
	}
	spin_unlock_irqrestore(&sossi.lock, flags);
	return IRQ_HANDLED;
}