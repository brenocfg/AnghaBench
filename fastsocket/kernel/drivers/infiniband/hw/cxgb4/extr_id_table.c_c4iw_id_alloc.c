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
struct c4iw_id_table {int max; int last; int flags; int /*<<< orphan*/  lock; scalar_t__ start; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int C4IW_ID_TABLE_F_RANDOM ; 
 int RANDOM_SKIP ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int random32 () ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 c4iw_id_alloc(struct c4iw_id_table *alloc)
{
	unsigned long flags;
	u32 obj;

	spin_lock_irqsave(&alloc->lock, flags);

	obj = find_next_zero_bit(alloc->table, alloc->max, alloc->last);
	if (obj >= alloc->max)
		obj = find_first_zero_bit(alloc->table, alloc->max);

	if (obj < alloc->max) {
		if (alloc->flags & C4IW_ID_TABLE_F_RANDOM)
			alloc->last += random32() % RANDOM_SKIP;
		else
			alloc->last = obj + 1;
		if (alloc->last >= alloc->max)
			alloc->last = 0;
		set_bit(obj, alloc->table);
		obj += alloc->start;
	} else
		obj = -1;

	spin_unlock_irqrestore(&alloc->lock, flags);
	return obj;
}