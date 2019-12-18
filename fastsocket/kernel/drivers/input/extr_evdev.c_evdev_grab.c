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
struct evdev_client {int dummy; } ;
struct evdev {scalar_t__ grab; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EBUSY ; 
 int input_grab_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct evdev_client*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int evdev_grab(struct evdev *evdev, struct evdev_client *client)
{
	int error;

	if (evdev->grab)
		return -EBUSY;

	error = input_grab_device(&evdev->handle);
	if (error)
		return error;

	rcu_assign_pointer(evdev->grab, client);
	synchronize_rcu();

	return 0;
}