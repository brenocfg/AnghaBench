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
struct rc_map {unsigned int size; unsigned int len; TYPE_1__* scan; int /*<<< orphan*/  alloc; int /*<<< orphan*/  rc_type; int /*<<< orphan*/  name; } ;
struct rc_dev {struct rc_map rc_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  keycode; int /*<<< orphan*/  scancode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IR_dprintk (int,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int ir_create_table (struct rc_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int ir_establish_scancode (struct rc_dev*,struct rc_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ir_free_table (struct rc_map*) ; 
 int /*<<< orphan*/  ir_update_mapping (struct rc_dev*,struct rc_map*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_setkeytable(struct rc_dev *dev,
			  const struct rc_map *from)
{
	struct rc_map *rc_map = &dev->rc_map;
	unsigned int i, index;
	int rc;

	rc = ir_create_table(rc_map, from->name,
			     from->rc_type, from->size);
	if (rc)
		return rc;

	IR_dprintk(1, "Allocated space for %u keycode entries (%u bytes)\n",
		   rc_map->size, rc_map->alloc);

	for (i = 0; i < from->size; i++) {
		index = ir_establish_scancode(dev, rc_map,
					      from->scan[i].scancode, false);
		if (index >= rc_map->len) {
			rc = -ENOMEM;
			break;
		}

		ir_update_mapping(dev, rc_map, index,
				  from->scan[i].keycode);
	}

	if (rc)
		ir_free_table(rc_map);

	return rc;
}