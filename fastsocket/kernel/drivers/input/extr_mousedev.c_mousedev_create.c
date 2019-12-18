#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  devt; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * class; } ;
struct TYPE_9__ {struct mousedev* private; struct input_handler* handler; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct mousedev {int minor; int exist; TYPE_1__ dev; TYPE_2__ handle; int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  client_lock; int /*<<< orphan*/  mixdev_node; int /*<<< orphan*/  client_list; } ;
struct input_handler {int dummy; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mousedev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MOUSEDEV_MINOR_BASE ; 
 int MOUSEDEV_MIX ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,...) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_class ; 
 int /*<<< orphan*/  input_get_device (struct input_dev*) ; 
 int input_register_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  input_unregister_handle (TYPE_2__*) ; 
 struct mousedev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mousedev_cleanup (struct mousedev*) ; 
 int /*<<< orphan*/  mousedev_free ; 
 int mousedev_install_chrdev (struct mousedev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mousedev *mousedev_create(struct input_dev *dev,
					struct input_handler *handler,
					int minor)
{
	struct mousedev *mousedev;
	int error;

	mousedev = kzalloc(sizeof(struct mousedev), GFP_KERNEL);
	if (!mousedev) {
		error = -ENOMEM;
		goto err_out;
	}

	INIT_LIST_HEAD(&mousedev->client_list);
	INIT_LIST_HEAD(&mousedev->mixdev_node);
	spin_lock_init(&mousedev->client_lock);
	mutex_init(&mousedev->mutex);
	lockdep_set_subclass(&mousedev->mutex,
			     minor == MOUSEDEV_MIX ? MOUSEDEV_MIX : 0);
	init_waitqueue_head(&mousedev->wait);

	if (minor == MOUSEDEV_MIX)
		dev_set_name(&mousedev->dev, "mice");
	else
		dev_set_name(&mousedev->dev, "mouse%d", minor);

	mousedev->minor = minor;
	mousedev->exist = 1;
	mousedev->handle.dev = input_get_device(dev);
	mousedev->handle.name = dev_name(&mousedev->dev);
	mousedev->handle.handler = handler;
	mousedev->handle.private = mousedev;

	mousedev->dev.class = &input_class;
	if (dev)
		mousedev->dev.parent = &dev->dev;
	mousedev->dev.devt = MKDEV(INPUT_MAJOR, MOUSEDEV_MINOR_BASE + minor);
	mousedev->dev.release = mousedev_free;
	device_initialize(&mousedev->dev);

	if (minor != MOUSEDEV_MIX) {
		error = input_register_handle(&mousedev->handle);
		if (error)
			goto err_free_mousedev;
	}

	error = mousedev_install_chrdev(mousedev);
	if (error)
		goto err_unregister_handle;

	error = device_add(&mousedev->dev);
	if (error)
		goto err_cleanup_mousedev;

	return mousedev;

 err_cleanup_mousedev:
	mousedev_cleanup(mousedev);
 err_unregister_handle:
	if (minor != MOUSEDEV_MIX)
		input_unregister_handle(&mousedev->handle);
 err_free_mousedev:
	put_device(&mousedev->dev);
 err_out:
	return ERR_PTR(error);
}