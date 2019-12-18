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
typedef  scalar_t__ u32 ;
struct mlx4_bitmap {int /*<<< orphan*/  table; scalar_t__ max; int /*<<< orphan*/  lock; scalar_t__ avail; scalar_t__ reserved_top; scalar_t__ mask; scalar_t__ top; scalar_t__ last; } ;

/* Variables and functions */
 int BITS_TO_LONGS (scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup_pow_of_two (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx4_bitmap_init(struct mlx4_bitmap *bitmap, u32 num, u32 mask,
		     u32 reserved_bot, u32 reserved_top)
{
	/* num must be a power of 2 */
	if (num != roundup_pow_of_two(num))
		return -EINVAL;

	bitmap->last = 0;
	bitmap->top  = 0;
	bitmap->max  = num - reserved_top;
	bitmap->mask = mask;
	bitmap->reserved_top = reserved_top;
	bitmap->avail = num - reserved_top - reserved_bot;
	spin_lock_init(&bitmap->lock);
	bitmap->table = kzalloc(BITS_TO_LONGS(bitmap->max) *
				sizeof (long), GFP_KERNEL);
	if (!bitmap->table)
		return -ENOMEM;

	bitmap_set(bitmap->table, 0, reserved_bot);

	return 0;
}