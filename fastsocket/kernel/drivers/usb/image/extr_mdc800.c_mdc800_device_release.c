#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  io_lock; scalar_t__ open; int /*<<< orphan*/  download_urb; int /*<<< orphan*/  write_urb; int /*<<< orphan*/  irq_urb; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ NOT_CONNECTED ; 
 int /*<<< orphan*/  dbg (char*) ; 
 TYPE_1__* mdc800 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdc800_device_release (struct inode* inode, struct file *file)
{
	int retval=0;
	dbg ("Mustek MDC800 device closed.");

	mutex_lock(&mdc800->io_lock);
	if (mdc800->open && (mdc800->state != NOT_CONNECTED))
	{
		usb_kill_urb(mdc800->irq_urb);
		usb_kill_urb(mdc800->write_urb);
		usb_kill_urb(mdc800->download_urb);
		mdc800->open=0;
	}
	else
	{
		retval=-EIO;
	}

	mutex_unlock(&mdc800->io_lock);
	return retval;
}