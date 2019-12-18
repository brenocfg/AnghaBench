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
struct evdev_client {struct evdev* evdev; int /*<<< orphan*/  buffer_lock; } ;
struct evdev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EVDEV_MINORS ; 
 int EVDEV_MINOR_BASE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  evdev_attach_client (struct evdev*,struct evdev_client*) ; 
 int /*<<< orphan*/  evdev_detach_client (struct evdev*,struct evdev_client*) ; 
 int evdev_open_device (struct evdev*) ; 
 struct evdev** evdev_table ; 
 int /*<<< orphan*/  evdev_table_mutex ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct evdev_client*) ; 
 struct evdev_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evdev_open(struct inode *inode, struct file *file)
{
	struct evdev *evdev;
	struct evdev_client *client;
	int i = iminor(inode) - EVDEV_MINOR_BASE;
	int error;

	if (i >= EVDEV_MINORS)
		return -ENODEV;

	error = mutex_lock_interruptible(&evdev_table_mutex);
	if (error)
		return error;
	evdev = evdev_table[i];
	if (evdev)
		get_device(&evdev->dev);
	mutex_unlock(&evdev_table_mutex);

	if (!evdev)
		return -ENODEV;

	client = kzalloc(sizeof(struct evdev_client), GFP_KERNEL);
	if (!client) {
		error = -ENOMEM;
		goto err_put_evdev;
	}

	spin_lock_init(&client->buffer_lock);
	client->evdev = evdev;
	evdev_attach_client(evdev, client);

	error = evdev_open_device(evdev);
	if (error)
		goto err_free_client;

	file->private_data = client;
	return 0;

 err_free_client:
	evdev_detach_client(evdev, client);
	kfree(client);
 err_put_evdev:
	put_device(&evdev->dev);
	return error;
}