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
struct omap24xxcam_dma {int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap24xxcam_dmahw_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap24xxcam_dma_hwinit(struct omap24xxcam_dma *dma)
{
	unsigned long flags;

	spin_lock_irqsave(&dma->lock, flags);

	omap24xxcam_dmahw_init(dma->base);

	spin_unlock_irqrestore(&dma->lock, flags);
}