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
struct dma_iso_ctx {unsigned int* buffer_status; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline unsigned video1394_buffer_state(struct dma_iso_ctx *d,
					      unsigned int buffer)
{
	unsigned long flags;
	unsigned int ret;
	spin_lock_irqsave(&d->lock, flags);
	ret = d->buffer_status[buffer];
	spin_unlock_irqrestore(&d->lock, flags);
	return ret;
}