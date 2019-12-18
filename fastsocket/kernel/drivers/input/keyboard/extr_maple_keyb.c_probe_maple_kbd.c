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
struct maple_driver {int dummy; } ;
struct maple_device {struct maple_driver* driver; int /*<<< orphan*/  dev; int /*<<< orphan*/  product_name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int* evbit; int keycodesize; int /*<<< orphan*/  keybit; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  keycodemax; int /*<<< orphan*/  keycode; int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct dc_kbd {int /*<<< orphan*/  keycode; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  MAPLE_FUNC_KEYBOARD ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int NR_SCANCODES ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_kbd_callback ; 
 int /*<<< orphan*/ * dc_kbd_keycode ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct dc_kbd*) ; 
 int /*<<< orphan*/  kfree (struct dc_kbd*) ; 
 struct dc_kbd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_getcond_callback (struct maple_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_set_drvdata (struct maple_device*,struct dc_kbd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct maple_device* to_maple_dev (struct device*) ; 
 struct maple_driver* to_maple_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_maple_kbd(struct device *dev)
{
	struct maple_device *mdev;
	struct maple_driver *mdrv;
	int i, error;
	struct dc_kbd *kbd;
	struct input_dev *idev;

	mdev = to_maple_dev(dev);
	mdrv = to_maple_driver(dev->driver);

	kbd = kzalloc(sizeof(struct dc_kbd), GFP_KERNEL);
	if (!kbd) {
		error = -ENOMEM;
		goto fail;
	}

	idev = input_allocate_device();
	if (!idev) {
		error = -ENOMEM;
		goto fail_idev_alloc;
	}

	kbd->dev = idev;
	memcpy(kbd->keycode, dc_kbd_keycode, sizeof(kbd->keycode));

	idev->name = mdev->product_name;
	idev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);
	idev->keycode = kbd->keycode;
	idev->keycodesize = sizeof(unsigned short);
	idev->keycodemax = ARRAY_SIZE(kbd->keycode);
	idev->id.bustype = BUS_HOST;
	idev->dev.parent = &mdev->dev;

	for (i = 0; i < NR_SCANCODES; i++)
		__set_bit(dc_kbd_keycode[i], idev->keybit);
	__clear_bit(KEY_RESERVED, idev->keybit);

	input_set_capability(idev, EV_MSC, MSC_SCAN);
	input_set_drvdata(idev, kbd);

	error = input_register_device(idev);
	if (error)
		goto fail_register;

	/* Maple polling is locked to VBLANK - which may be just 50/s */
	maple_getcond_callback(mdev, dc_kbd_callback, HZ/50,
		MAPLE_FUNC_KEYBOARD);

	mdev->driver = mdrv;

	maple_set_drvdata(mdev, kbd);

	return error;

fail_register:
	maple_set_drvdata(mdev, NULL);
	input_free_device(idev);
fail_idev_alloc:
	kfree(kbd);
fail:
	return error;
}