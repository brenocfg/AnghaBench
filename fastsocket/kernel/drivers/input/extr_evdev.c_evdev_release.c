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
struct inode {int dummy; } ;
struct file {struct evdev_client* private_data; } ;
struct evdev_client {struct evdev* evdev; } ;
struct evdev {int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; struct evdev_client* grab; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdev_close_device (struct evdev*) ; 
 int /*<<< orphan*/  evdev_detach_client (struct evdev*,struct evdev_client*) ; 
 int /*<<< orphan*/  evdev_ungrab (struct evdev*,struct evdev_client*) ; 
 int /*<<< orphan*/  kfree (struct evdev_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evdev_release(struct inode *inode, struct file *file)
{
	struct evdev_client *client = file->private_data;
	struct evdev *evdev = client->evdev;

	mutex_lock(&evdev->mutex);
	if (evdev->grab == client)
		evdev_ungrab(evdev, client);
	mutex_unlock(&evdev->mutex);

	evdev_detach_client(evdev, client);
	kfree(client);

	evdev_close_device(evdev);
	put_device(&evdev->dev);

	return 0;
}