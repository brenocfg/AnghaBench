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
struct joydev_client {struct joydev* joydev; int /*<<< orphan*/  buffer_lock; } ;
struct joydev {int /*<<< orphan*/  dev; } ;
struct inode {int dummy; } ;
struct file {struct joydev_client* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JOYDEV_MINORS ; 
 int JOYDEV_MINOR_BASE ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  joydev_attach_client (struct joydev*,struct joydev_client*) ; 
 int /*<<< orphan*/  joydev_detach_client (struct joydev*,struct joydev_client*) ; 
 int joydev_open_device (struct joydev*) ; 
 struct joydev** joydev_table ; 
 int /*<<< orphan*/  joydev_table_mutex ; 
 int /*<<< orphan*/  kfree (struct joydev_client*) ; 
 struct joydev_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int joydev_open(struct inode *inode, struct file *file)
{
	struct joydev_client *client;
	struct joydev *joydev;
	int i = iminor(inode) - JOYDEV_MINOR_BASE;
	int error;

	if (i >= JOYDEV_MINORS)
		return -ENODEV;

	error = mutex_lock_interruptible(&joydev_table_mutex);
	if (error)
		return error;
	joydev = joydev_table[i];
	if (joydev)
		get_device(&joydev->dev);
	mutex_unlock(&joydev_table_mutex);

	if (!joydev)
		return -ENODEV;

	client = kzalloc(sizeof(struct joydev_client), GFP_KERNEL);
	if (!client) {
		error = -ENOMEM;
		goto err_put_joydev;
	}

	spin_lock_init(&client->buffer_lock);
	client->joydev = joydev;
	joydev_attach_client(joydev, client);

	error = joydev_open_device(joydev);
	if (error)
		goto err_free_client;

	file->private_data = client;
	return 0;

 err_free_client:
	joydev_detach_client(joydev, client);
	kfree(client);
 err_put_joydev:
	put_device(&joydev->dev);
	return error;
}