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
struct rc_map {unsigned int len; int /*<<< orphan*/  lock; TYPE_1__* scan; } ;
struct rc_dev {struct rc_map rc_map; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int keycode; } ;

/* Variables and functions */
 int KEY_RESERVED ; 
 struct rc_dev* input_get_drvdata (struct input_dev*) ; 
 unsigned int ir_lookup_by_scancode (struct rc_map*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ir_getkeycode(struct input_dev *idev,
			 int scancode, int *keycode)
{
	struct rc_dev *rdev = input_get_drvdata(idev);
	struct rc_map *rc_map = &rdev->rc_map;
	unsigned long flags;
	unsigned int index;
	int retval;

	spin_lock_irqsave(&rc_map->lock, flags);

	index = ir_lookup_by_scancode(rc_map, scancode);

	if (index >= rc_map->len) {
		*keycode = KEY_RESERVED;
		retval = 0;
		goto out;
	}

	*keycode = rc_map->scan[index].keycode;

	retval = 0;

out:
	spin_unlock_irqrestore(&rc_map->lock, flags);
	return retval;
}