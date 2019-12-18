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
typedef  scalar_t__ u32 ;
struct c2_pd {scalar_t__ pd_id; } ;
struct TYPE_2__ {scalar_t__ max; scalar_t__ last; int /*<<< orphan*/  lock; int /*<<< orphan*/  table; } ;
struct c2_dev {TYPE_1__ pd_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ find_next_zero_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int c2_pd_alloc(struct c2_dev *c2dev, int privileged, struct c2_pd *pd)
{
	u32 obj;
	int ret = 0;

	spin_lock(&c2dev->pd_table.lock);
	obj = find_next_zero_bit(c2dev->pd_table.table, c2dev->pd_table.max,
				 c2dev->pd_table.last);
	if (obj >= c2dev->pd_table.max)
		obj = find_first_zero_bit(c2dev->pd_table.table,
					  c2dev->pd_table.max);
	if (obj < c2dev->pd_table.max) {
		pd->pd_id = obj;
		__set_bit(obj, c2dev->pd_table.table);
		c2dev->pd_table.last = obj+1;
		if (c2dev->pd_table.last >= c2dev->pd_table.max)
			c2dev->pd_table.last = 0;
	} else
		ret = -ENOMEM;
	spin_unlock(&c2dev->pd_table.lock);
	return ret;
}