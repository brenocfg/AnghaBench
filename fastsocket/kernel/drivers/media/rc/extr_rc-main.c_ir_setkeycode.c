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
struct rc_map {unsigned int len; int /*<<< orphan*/  lock; } ;
struct rc_dev {struct rc_map rc_map; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct rc_dev* input_get_drvdata (struct input_dev*) ; 
 unsigned int ir_establish_scancode (struct rc_dev*,struct rc_map*,int,int) ; 
 int /*<<< orphan*/  ir_update_mapping (struct rc_dev*,struct rc_map*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ir_setkeycode(struct input_dev *idev,
			 int scancode, int keycode)
{
	struct rc_dev *rdev = input_get_drvdata(idev);
	struct rc_map *rc_map = &rdev->rc_map;
	unsigned int index;
	int retval = 0;
	unsigned long flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	index = ir_establish_scancode(rdev, rc_map, scancode, true);
	if (index >= rc_map->len) {
		retval = -ENOMEM;
		goto out;
	}

	ir_update_mapping(rdev, rc_map, index, keycode);

out:
	spin_unlock_irqrestore(&rc_map->lock, flags);
	return retval;
}