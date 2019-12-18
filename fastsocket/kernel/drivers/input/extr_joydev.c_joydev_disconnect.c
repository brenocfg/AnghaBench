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
struct joydev {int /*<<< orphan*/  dev; } ;
struct input_handle {struct joydev* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_handle (struct input_handle*) ; 
 int /*<<< orphan*/  joydev_cleanup (struct joydev*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void joydev_disconnect(struct input_handle *handle)
{
	struct joydev *joydev = handle->private;

	device_del(&joydev->dev);
	joydev_cleanup(joydev);
	input_unregister_handle(handle);
	put_device(&joydev->dev);
}