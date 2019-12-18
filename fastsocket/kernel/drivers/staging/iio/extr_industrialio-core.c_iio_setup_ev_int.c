#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  devt; int /*<<< orphan*/ * type; struct device* parent; int /*<<< orphan*/ * class; } ;
struct TYPE_13__ {struct module* owner; } ;
struct TYPE_11__ {TYPE_8__ chrdev; scalar_t__ flags; struct iio_event_interface* private; } ;
struct TYPE_10__ {int /*<<< orphan*/  list; } ;
struct iio_event_interface {int max_events; TYPE_3__ dev; TYPE_2__ handler; int /*<<< orphan*/  wait; TYPE_1__ det_events; scalar_t__ current_events; int /*<<< orphan*/  event_list_lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int cdev_add (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,char const*) ; 
 int device_add (TYPE_3__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_class ; 
 int /*<<< orphan*/  iio_device_free_chrdev_minor (int) ; 
 int iio_device_get_chrdev_minor () ; 
 int /*<<< orphan*/  iio_devt ; 
 int /*<<< orphan*/  iio_event_chrdev_fileops ; 
 int /*<<< orphan*/  iio_event_type ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 

int iio_setup_ev_int(struct iio_event_interface *ev_int,
		     const char *name,
		     struct module *owner,
		     struct device *dev)
{
	int ret, minor;

	ev_int->dev.class = &iio_class;
	ev_int->dev.parent = dev;
	ev_int->dev.type = &iio_event_type;
	device_initialize(&ev_int->dev);

	minor = iio_device_get_chrdev_minor();
	if (minor < 0) {
		ret = minor;
		goto error_device_put;
	}
	ev_int->dev.devt = MKDEV(MAJOR(iio_devt), minor);
	dev_set_name(&ev_int->dev, "%s", name);

	ret = device_add(&ev_int->dev);
	if (ret)
		goto error_free_minor;

	cdev_init(&ev_int->handler.chrdev, &iio_event_chrdev_fileops);
	ev_int->handler.chrdev.owner = owner;

	mutex_init(&ev_int->event_list_lock);
	/* discussion point - make this variable? */
	ev_int->max_events = 10;
	ev_int->current_events = 0;
	INIT_LIST_HEAD(&ev_int->det_events.list);
	init_waitqueue_head(&ev_int->wait);
	ev_int->handler.private = ev_int;
	ev_int->handler.flags = 0;

	ret = cdev_add(&ev_int->handler.chrdev, ev_int->dev.devt, 1);
	if (ret)
		goto error_unreg_device;

	return 0;

error_unreg_device:
	device_unregister(&ev_int->dev);
error_free_minor:
	iio_device_free_chrdev_minor(minor);
error_device_put:
	put_device(&ev_int->dev);

	return ret;
}