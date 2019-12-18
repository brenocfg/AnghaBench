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
struct sisusb_usb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  sisusb_dev; int /*<<< orphan*/  ready; int /*<<< orphan*/  present; } ;
struct file {int /*<<< orphan*/  f_pos; scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t
sisusb_lseek(struct file *file, loff_t offset, int orig)
{
	struct sisusb_usb_data *sisusb;
	loff_t ret;

	if (!(sisusb = (struct sisusb_usb_data *)file->private_data))
		return -ENODEV;

	mutex_lock(&sisusb->lock);

	/* Sanity check */
	if (!sisusb->present || !sisusb->ready || !sisusb->sisusb_dev) {
		mutex_unlock(&sisusb->lock);
		return -ENODEV;
	}

	switch (orig) {
		case 0:
			file->f_pos = offset;
			ret = file->f_pos;
			/* never negative, no force_successful_syscall needed */
			break;
		case 1:
			file->f_pos += offset;
			ret = file->f_pos;
			/* never negative, no force_successful_syscall needed */
			break;
		default:
			/* seeking relative to "end of file" is not supported */
			ret = -EINVAL;
	}

	mutex_unlock(&sisusb->lock);
	return ret;
}