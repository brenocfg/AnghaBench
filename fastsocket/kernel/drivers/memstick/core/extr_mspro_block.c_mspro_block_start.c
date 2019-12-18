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
struct mspro_block_data {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  queue; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_start_queue (int /*<<< orphan*/ ) ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mspro_block_start(struct memstick_dev *card)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	unsigned long flags;

	spin_lock_irqsave(&msb->q_lock, flags);
	blk_start_queue(msb->queue);
	spin_unlock_irqrestore(&msb->q_lock, flags);
}