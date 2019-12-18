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
struct input_polled_dev {int poll_interval; int /*<<< orphan*/  work; struct input_dev* input; } ;
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_close_polled_device ; 
 int /*<<< orphan*/  input_open_polled_device ; 
 int /*<<< orphan*/  input_polled_device_work ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct input_polled_dev*) ; 

int input_register_polled_device(struct input_polled_dev *dev)
{
	struct input_dev *input = dev->input;

	input_set_drvdata(input, dev);
	INIT_DELAYED_WORK(&dev->work, input_polled_device_work);
	if (!dev->poll_interval)
		dev->poll_interval = 500;
	input->open = input_open_polled_device;
	input->close = input_close_polled_device;

	return input_register_device(input);
}