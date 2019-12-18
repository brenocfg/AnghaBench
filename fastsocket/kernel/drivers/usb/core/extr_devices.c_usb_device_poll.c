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
struct usb_device_status {scalar_t__ lastev; } ;
struct poll_table_struct {int dummy; } ;
struct file {int f_mode; struct usb_device_status* private_data; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int POLLIN ; 
 scalar_t__ conndiscevcnt ; 
 int /*<<< orphan*/  deviceconndiscwq ; 
 int /*<<< orphan*/  kfree (struct usb_device_status*) ; 
 struct usb_device_status* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static unsigned int usb_device_poll(struct file *file,
				    struct poll_table_struct *wait)
{
	struct usb_device_status *st = file->private_data;
	unsigned int mask = 0;

	lock_kernel();
	if (!st) {
		st = kmalloc(sizeof(struct usb_device_status), GFP_KERNEL);

		/* we may have dropped BKL -
		 * need to check for having lost the race */
		if (file->private_data) {
			kfree(st);
			st = file->private_data;
			goto lost_race;
		}
		/* we haven't lost - check for allocation failure now */
		if (!st) {
			unlock_kernel();
			return POLLIN;
		}

		/*
		 * need to prevent the module from being unloaded, since
		 * proc_unregister does not call the release method and
		 * we would have a memory leak
		 */
		st->lastev = conndiscevcnt;
		file->private_data = st;
		mask = POLLIN;
	}
lost_race:
	if (file->f_mode & FMODE_READ)
		poll_wait(file, &deviceconndiscwq, wait);
	if (st->lastev != conndiscevcnt)
		mask |= POLLIN;
	st->lastev = conndiscevcnt;
	unlock_kernel();
	return mask;
}