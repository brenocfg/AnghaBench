#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uinput_device {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* input_allocate_device () ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_1__*,struct uinput_device*) ; 
 int /*<<< orphan*/  uinput_dev_event ; 

__attribute__((used)) static int uinput_allocate_device(struct uinput_device *udev)
{
	udev->dev = input_allocate_device();
	if (!udev->dev)
		return -ENOMEM;

	udev->dev->event = uinput_dev_event;
	input_set_drvdata(udev->dev, udev);

	return 0;
}