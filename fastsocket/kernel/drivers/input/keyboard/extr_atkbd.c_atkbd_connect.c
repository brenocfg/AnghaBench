#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct serio_driver {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int type; } ;
struct serio {TYPE_2__ dev; int /*<<< orphan*/  write; TYPE_1__ id; } ;
struct input_dev {int dummy; } ;
struct atkbd {int translated; int write; int softraw; int set; int id; struct input_dev* dev; scalar_t__ softrepeat; int /*<<< orphan*/  scroll; int /*<<< orphan*/  event_mutex; int /*<<< orphan*/  event_work; int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SERIO_8042 129 
#define  SERIO_8042_XL 128 
 int /*<<< orphan*/  atkbd_activate (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_attribute_group ; 
 int /*<<< orphan*/  atkbd_enable (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_event_work ; 
 int /*<<< orphan*/  atkbd_extra ; 
 scalar_t__ atkbd_probe (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_reset_state (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_scroll ; 
 int atkbd_select_set (struct atkbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atkbd_set ; 
 int /*<<< orphan*/  atkbd_set_device_attrs (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_set_keycode_table (struct atkbd*) ; 
 int atkbd_softraw ; 
 scalar_t__ atkbd_softrepeat ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct atkbd*) ; 
 struct atkbd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps2_init (int /*<<< orphan*/ *,struct serio*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct atkbd*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atkbd_connect(struct serio *serio, struct serio_driver *drv)
{
	struct atkbd *atkbd;
	struct input_dev *dev;
	int err = -ENOMEM;

	atkbd = kzalloc(sizeof(struct atkbd), GFP_KERNEL);
	dev = input_allocate_device();
	if (!atkbd || !dev)
		goto fail1;

	atkbd->dev = dev;
	ps2_init(&atkbd->ps2dev, serio);
	INIT_DELAYED_WORK(&atkbd->event_work, atkbd_event_work);
	mutex_init(&atkbd->event_mutex);

	switch (serio->id.type) {

		case SERIO_8042_XL:
			atkbd->translated = 1;
		case SERIO_8042:
			if (serio->write)
				atkbd->write = 1;
			break;
	}

	atkbd->softraw = atkbd_softraw;
	atkbd->softrepeat = atkbd_softrepeat;
	atkbd->scroll = atkbd_scroll;

	if (atkbd->softrepeat)
		atkbd->softraw = 1;

	serio_set_drvdata(serio, atkbd);

	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	if (atkbd->write) {

		if (atkbd_probe(atkbd)) {
			err = -ENODEV;
			goto fail3;
		}

		atkbd->set = atkbd_select_set(atkbd, atkbd_set, atkbd_extra);
		atkbd_reset_state(atkbd);
		atkbd_activate(atkbd);

	} else {
		atkbd->set = 2;
		atkbd->id = 0xab00;
	}

	atkbd_set_keycode_table(atkbd);
	atkbd_set_device_attrs(atkbd);

	err = sysfs_create_group(&serio->dev.kobj, &atkbd_attribute_group);
	if (err)
		goto fail3;

	atkbd_enable(atkbd);

	err = input_register_device(atkbd->dev);
	if (err)
		goto fail4;

	return 0;

 fail4: sysfs_remove_group(&serio->dev.kobj, &atkbd_attribute_group);
 fail3:	serio_close(serio);
 fail2:	serio_set_drvdata(serio, NULL);
 fail1:	input_free_device(dev);
	kfree(atkbd);
	return err;
}