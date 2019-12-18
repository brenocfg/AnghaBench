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
struct sidtab {int /*<<< orphan*/  lock; scalar_t__ shutdown; int /*<<< orphan*/  next_sid; int /*<<< orphan*/  nel; int /*<<< orphan*/  htable; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sidtab_set(struct sidtab *dst, struct sidtab *src)
{
	unsigned long flags;

	spin_lock_irqsave(&src->lock, flags);
	dst->htable = src->htable;
	dst->nel = src->nel;
	dst->next_sid = src->next_sid;
	dst->shutdown = 0;
	spin_unlock_irqrestore(&src->lock, flags);
}