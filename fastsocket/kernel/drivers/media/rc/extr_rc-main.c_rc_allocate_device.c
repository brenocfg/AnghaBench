#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * class; int /*<<< orphan*/ * type; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct rc_dev {TYPE_4__ dev; int /*<<< orphan*/  timer_keyup; int /*<<< orphan*/  keylock; TYPE_1__ rc_map; TYPE_2__* input_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  setkeycode; int /*<<< orphan*/  getkeycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_4__*) ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct rc_dev*) ; 
 int /*<<< orphan*/  ir_getkeycode ; 
 int /*<<< orphan*/  ir_input_class ; 
 int /*<<< orphan*/  ir_setkeycode ; 
 int /*<<< orphan*/  ir_timer_keyup ; 
 int /*<<< orphan*/  kfree (struct rc_dev*) ; 
 struct rc_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_dev_type ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct rc_dev *rc_allocate_device(void)
{
	struct rc_dev *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	dev->input_dev = input_allocate_device();
	if (!dev->input_dev) {
		kfree(dev);
		return NULL;
	}

	dev->input_dev->getkeycode = ir_getkeycode;
	dev->input_dev->setkeycode = ir_setkeycode;
	input_set_drvdata(dev->input_dev, dev);

	spin_lock_init(&dev->rc_map.lock);
	spin_lock_init(&dev->keylock);
	setup_timer(&dev->timer_keyup, ir_timer_keyup, (unsigned long)dev);

	dev->dev.type = &rc_dev_type;
	dev->dev.class = &ir_input_class;
	device_initialize(&dev->dev);

	__module_get(THIS_MODULE);
	return dev;
}