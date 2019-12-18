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
struct request_queue {struct cardinfo* queuedata; } ;
struct cardinfo {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  activate (struct cardinfo*) ; 
 scalar_t__ blk_remove_plug (struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mm_unplug_device(struct request_queue *q)
{
	struct cardinfo *card = q->queuedata;
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);
	if (blk_remove_plug(q))
		activate(card);
	spin_unlock_irqrestore(&card->lock, flags);
}