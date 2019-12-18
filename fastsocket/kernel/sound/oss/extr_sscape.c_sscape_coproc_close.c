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
struct sscape_info {int /*<<< orphan*/  lock; scalar_t__ dma_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  GA_DMAA_REG ; 
 int /*<<< orphan*/  __sscape_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sscape_coproc_close(void *dev_info, int sub_device)
{
	struct sscape_info *devc = dev_info;
	unsigned long   flags;

	spin_lock_irqsave(&devc->lock,flags);
	if (devc->dma_allocated)
	{
		__sscape_write(GA_DMAA_REG, 0x20);	/* DMA channel disabled */
		devc->dma_allocated = 0;
	}
	spin_unlock_irqrestore(&devc->lock,flags);
	return;
}