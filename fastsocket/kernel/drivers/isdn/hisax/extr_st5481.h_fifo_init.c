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
struct fifo {int size; int /*<<< orphan*/  lock; scalar_t__ count; scalar_t__ w; scalar_t__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fifo_init(struct fifo *fifo, int size)
{
	fifo->r = fifo->w = fifo->count = 0;
	fifo->size = size;
	spin_lock_init(&fifo->lock);
}