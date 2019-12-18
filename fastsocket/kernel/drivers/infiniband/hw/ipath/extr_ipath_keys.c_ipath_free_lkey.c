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
typedef  int u32 ;
struct ipath_lkey_table {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** table; } ;

/* Variables and functions */
 int ib_ipath_lkey_table_size ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipath_free_lkey(struct ipath_lkey_table *rkt, u32 lkey)
{
	unsigned long flags;
	u32 r;

	if (lkey == 0)
		return;
	r = lkey >> (32 - ib_ipath_lkey_table_size);
	spin_lock_irqsave(&rkt->lock, flags);
	rkt->table[r] = NULL;
	spin_unlock_irqrestore(&rkt->lock, flags);
}