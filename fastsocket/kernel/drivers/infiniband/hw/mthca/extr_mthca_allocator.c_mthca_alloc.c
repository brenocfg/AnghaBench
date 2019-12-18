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
struct mthca_alloc {int max; int top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  table; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 mthca_alloc(struct mthca_alloc *alloc)
{
	unsigned long flags;
	u32 obj;

	spin_lock_irqsave(&alloc->lock, flags);

	obj = find_next_zero_bit(alloc->table, alloc->max, alloc->last);
	if (obj >= alloc->max) {
		alloc->top = (alloc->top + alloc->max) & alloc->mask;
		obj = find_first_zero_bit(alloc->table, alloc->max);
	}

	if (obj < alloc->max) {
		set_bit(obj, alloc->table);
		obj |= alloc->top;
	} else
		obj = -1;

	spin_unlock_irqrestore(&alloc->lock, flags);

	return obj;
}