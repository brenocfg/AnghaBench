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
struct TYPE_2__ {int effect_id; } ;
struct uinput_request {int id; int retval; int /*<<< orphan*/  done; TYPE_1__ u; int /*<<< orphan*/  code; } ;
struct uinput_device {int dummy; } ;
struct input_dev {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  UI_FF_ERASE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct uinput_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uinput_request_submit (struct uinput_device*,struct uinput_request*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uinput_dev_erase_effect(struct input_dev *dev, int effect_id)
{
	struct uinput_device *udev = input_get_drvdata(dev);
	struct uinput_request request;
	int retval;

	if (!test_bit(EV_FF, dev->evbit))
		return -ENOSYS;

	request.id = -1;
	init_completion(&request.done);
	request.code = UI_FF_ERASE;
	request.u.effect_id = effect_id;

	retval = uinput_request_submit(udev, &request);
	if (!retval) {
		wait_for_completion(&request.done);
		retval = request.retval;
	}

	return retval;
}