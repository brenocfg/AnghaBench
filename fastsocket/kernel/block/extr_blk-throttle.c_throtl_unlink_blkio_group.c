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
struct throtl_data {TYPE_1__* queue; } ;
struct blkio_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tg_of_blkg (struct blkio_group*) ; 
 int /*<<< orphan*/  throtl_destroy_tg (struct throtl_data*,int /*<<< orphan*/ ) ; 

void throtl_unlink_blkio_group(void *key, struct blkio_group *blkg)
{
	unsigned long flags;
	struct throtl_data *td = key;

	spin_lock_irqsave(td->queue->queue_lock, flags);
	throtl_destroy_tg(td, tg_of_blkg(blkg));
	spin_unlock_irqrestore(td->queue->queue_lock, flags);
}