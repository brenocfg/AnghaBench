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
struct ucb1x00_ts {TYPE_2__* ucb; int /*<<< orphan*/  adcsync; struct input_dev* idev; } ;
struct ucb1x00_dev {struct ucb1x00_ts* priv; TYPE_2__* ucb; } ;
struct TYPE_3__ {int /*<<< orphan*/  product; } ;
struct input_dev {char* name; int /*<<< orphan*/  absbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UCB_NOSYNC ; 
 int /*<<< orphan*/  UCB_SYNC ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ adcsync ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  kfree (struct ucb1x00_ts*) ; 
 struct ucb1x00_ts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1x00_ts_close ; 
 int /*<<< orphan*/  ucb1x00_ts_open ; 

__attribute__((used)) static int ucb1x00_ts_add(struct ucb1x00_dev *dev)
{
	struct ucb1x00_ts *ts;
	struct input_dev *idev;
	int err;

	ts = kzalloc(sizeof(struct ucb1x00_ts), GFP_KERNEL);
	idev = input_allocate_device();
	if (!ts || !idev) {
		err = -ENOMEM;
		goto fail;
	}

	ts->ucb = dev->ucb;
	ts->idev = idev;
	ts->adcsync = adcsync ? UCB_SYNC : UCB_NOSYNC;

	idev->name       = "Touchscreen panel";
	idev->id.product = ts->ucb->id;
	idev->open       = ucb1x00_ts_open;
	idev->close      = ucb1x00_ts_close;

	__set_bit(EV_ABS, idev->evbit);
	__set_bit(ABS_X, idev->absbit);
	__set_bit(ABS_Y, idev->absbit);
	__set_bit(ABS_PRESSURE, idev->absbit);

	input_set_drvdata(idev, ts);

	err = input_register_device(idev);
	if (err)
		goto fail;

	dev->priv = ts;

	return 0;

 fail:
	input_free_device(idev);
	kfree(ts);
	return err;
}