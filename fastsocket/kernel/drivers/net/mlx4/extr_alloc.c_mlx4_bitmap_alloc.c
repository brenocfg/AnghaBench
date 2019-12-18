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
struct mlx4_bitmap {int max; int last; int top; int reserved_top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  avail; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

u32 mlx4_bitmap_alloc(struct mlx4_bitmap *bitmap)
{
	u32 obj;

	spin_lock(&bitmap->lock);

	obj = find_next_zero_bit(bitmap->table, bitmap->max, bitmap->last);
	if (obj >= bitmap->max) {
		bitmap->top = (bitmap->top + bitmap->max + bitmap->reserved_top)
				& bitmap->mask;
		obj = find_first_zero_bit(bitmap->table, bitmap->max);
	}

	if (obj < bitmap->max) {
		set_bit(obj, bitmap->table);
		bitmap->last = (obj + 1);
		if (bitmap->last == bitmap->max)
			bitmap->last = 0;
		obj |= bitmap->top;
	} else
		obj = -1;

	if (obj != -1)
		--bitmap->avail;

	spin_unlock(&bitmap->lock);

	return obj;
}