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
struct fifo {int count; int size; int /*<<< orphan*/  lock; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int fifo_add(struct fifo *fifo)
{
	unsigned long flags;
	int index;

	if (!fifo) {
		return -1;
	}

	spin_lock_irqsave(&fifo->lock, flags);
	if (fifo->count == fifo->size) {
		// FIFO full
		index = -1;
	} else {
		// Return index where to get the next data to add to the FIFO
		index = fifo->w++ & (fifo->size-1);
		fifo->count++;
	}
	spin_unlock_irqrestore(&fifo->lock, flags);
	return index;
}