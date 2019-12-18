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
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct iio_handler {struct iio_event_interface* private; int /*<<< orphan*/  flags; } ;
struct iio_event_interface {int /*<<< orphan*/  event_list_lock; } ;
struct file {struct iio_event_interface* private_data; int /*<<< orphan*/  f_op; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IIO_BUSY_BIT_POS ; 
 int /*<<< orphan*/  fops_put (int /*<<< orphan*/ ) ; 
 struct iio_handler* iio_cdev_to_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iio_event_chrdev_open(struct inode *inode, struct file *filep)
{
	struct iio_handler *hand = iio_cdev_to_handler(inode->i_cdev);
	struct iio_event_interface *ev_int = hand->private;

	mutex_lock(&ev_int->event_list_lock);
	if (test_and_set_bit(IIO_BUSY_BIT_POS, &hand->flags)) {
		fops_put(filep->f_op);
		mutex_unlock(&ev_int->event_list_lock);
		return -EBUSY;
	}
	filep->private_data = hand->private;
	mutex_unlock(&ev_int->event_list_lock);

	return 0;
}