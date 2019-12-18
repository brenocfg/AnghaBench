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
struct TYPE_2__ {int /*<<< orphan*/ * class; int /*<<< orphan*/ * type; } ;
struct input_dev {int /*<<< orphan*/  node; int /*<<< orphan*/  h_list; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  mutex; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  input_class ; 
 int /*<<< orphan*/  input_dev_type ; 
 struct input_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct input_dev *input_allocate_device(void)
{
	struct input_dev *dev;

	dev = kzalloc(sizeof(struct input_dev), GFP_KERNEL);
	if (dev) {
		dev->dev.type = &input_dev_type;
		dev->dev.class = &input_class;
		device_initialize(&dev->dev);
		mutex_init(&dev->mutex);
		spin_lock_init(&dev->event_lock);
		INIT_LIST_HEAD(&dev->h_list);
		INIT_LIST_HEAD(&dev->node);

		__module_get(THIS_MODULE);
	}

	return dev;
}