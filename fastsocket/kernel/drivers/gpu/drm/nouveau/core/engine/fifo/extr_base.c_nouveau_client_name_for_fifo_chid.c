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
typedef  size_t u32 ;
struct nouveau_fifo_chan {int dummy; } ;
struct nouveau_fifo {size_t min; size_t max; int /*<<< orphan*/  lock; scalar_t__* channel; } ;

/* Variables and functions */
 char const* nouveau_client_name (struct nouveau_fifo_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

const char *
nouveau_client_name_for_fifo_chid(struct nouveau_fifo *fifo, u32 chid)
{
	struct nouveau_fifo_chan *chan = NULL;
	unsigned long flags;

	spin_lock_irqsave(&fifo->lock, flags);
	if (chid >= fifo->min && chid <= fifo->max)
		chan = (void *)fifo->channel[chid];
	spin_unlock_irqrestore(&fifo->lock, flags);

	return nouveau_client_name(chan);
}