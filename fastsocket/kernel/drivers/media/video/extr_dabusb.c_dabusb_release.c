#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  TYPE_1__* pdabusb_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ opened; int /*<<< orphan*/  remove_ok; TYPE_2__* usbdev; int /*<<< orphan*/  remove_pending; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  _DABUSB_IF ; 
 int /*<<< orphan*/  dabusb_free_buffers (TYPE_1__*) ; 
 int /*<<< orphan*/  dabusb_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_set_interface (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dabusb_release (struct inode *inode, struct file *file)
{
	pdabusb_t s = (pdabusb_t) file->private_data;

	dbg("dabusb_release");

	mutex_lock(&s->mutex);
	dabusb_stop (s);
	dabusb_free_buffers (s);
	mutex_unlock(&s->mutex);

	if (!s->remove_pending) {
		if (usb_set_interface (s->usbdev, _DABUSB_IF, 0) < 0)
			dev_err(&s->usbdev->dev, "set_interface failed\n");
	}
	else
		wake_up (&s->remove_ok);

	s->opened = 0;
	return 0;
}