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
struct mousedev_client {int pos_x; int pos_y; struct mousedev* mousedev; int /*<<< orphan*/  packet_lock; } ;
struct mousedev {int /*<<< orphan*/  dev; } ;
struct inode {int dummy; } ;
struct file {struct mousedev_client* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MISC_MAJOR ; 
 int MOUSEDEV_MINORS ; 
 int MOUSEDEV_MINOR_BASE ; 
 int MOUSEDEV_MIX ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ imajor (struct inode*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct mousedev_client*) ; 
 struct mousedev_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mousedev_attach_client (struct mousedev*,struct mousedev_client*) ; 
 int /*<<< orphan*/  mousedev_detach_client (struct mousedev*,struct mousedev_client*) ; 
 int mousedev_open_device (struct mousedev*) ; 
 struct mousedev** mousedev_table ; 
 int /*<<< orphan*/  mousedev_table_mutex ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int xres ; 
 int yres ; 

__attribute__((used)) static int mousedev_open(struct inode *inode, struct file *file)
{
	struct mousedev_client *client;
	struct mousedev *mousedev;
	int error;
	int i;

#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
	if (imajor(inode) == MISC_MAJOR)
		i = MOUSEDEV_MIX;
	else
#endif
		i = iminor(inode) - MOUSEDEV_MINOR_BASE;

	if (i >= MOUSEDEV_MINORS)
		return -ENODEV;

	lock_kernel();
	error = mutex_lock_interruptible(&mousedev_table_mutex);
	if (error) {
		unlock_kernel();
		return error;
	}
	mousedev = mousedev_table[i];
	if (mousedev)
		get_device(&mousedev->dev);
	mutex_unlock(&mousedev_table_mutex);

	if (!mousedev) {
		unlock_kernel();
		return -ENODEV;
	}

	client = kzalloc(sizeof(struct mousedev_client), GFP_KERNEL);
	if (!client) {
		error = -ENOMEM;
		goto err_put_mousedev;
	}

	spin_lock_init(&client->packet_lock);
	client->pos_x = xres / 2;
	client->pos_y = yres / 2;
	client->mousedev = mousedev;
	mousedev_attach_client(mousedev, client);

	error = mousedev_open_device(mousedev);
	if (error)
		goto err_free_client;

	file->private_data = client;
	unlock_kernel();
	return 0;

 err_free_client:
	mousedev_detach_client(mousedev, client);
	kfree(client);
 err_put_mousedev:
	put_device(&mousedev->dev);
	unlock_kernel();
	return error;
}