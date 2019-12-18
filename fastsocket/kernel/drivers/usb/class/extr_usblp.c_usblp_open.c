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
struct usblp {int used; int wcomplete; scalar_t__ rcomplete; scalar_t__ wstatus; int /*<<< orphan*/  present; int /*<<< orphan*/  dev; } ;
struct usb_interface {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct usblp* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 scalar_t__ handle_bidir (struct usblp*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (struct usb_interface*) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int) ; 
 struct usblp* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usblp_driver ; 
 int /*<<< orphan*/  usblp_mutex ; 

__attribute__((used)) static int usblp_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	struct usblp *usblp;
	struct usb_interface *intf;
	int retval;

	if (minor < 0)
		return -ENODEV;

	mutex_lock (&usblp_mutex);

	retval = -ENODEV;
	intf = usb_find_interface(&usblp_driver, minor);
	if (!intf) {
		goto out;
	}
	usblp = usb_get_intfdata (intf);
	if (!usblp || !usblp->dev || !usblp->present)
		goto out;

	retval = -EBUSY;
	if (usblp->used)
		goto out;

	/*
	 * We do not implement LP_ABORTOPEN/LPABORTOPEN for two reasons:
	 *  - We do not want persistent state which close(2) does not clear
	 *  - It is not used anyway, according to CUPS people
	 */

	retval = usb_autopm_get_interface(intf);
	if (retval < 0)
		goto out;
	usblp->used = 1;
	file->private_data = usblp;

	usblp->wcomplete = 1; /* we begin writeable */
	usblp->wstatus = 0;
	usblp->rcomplete = 0;

	if (handle_bidir(usblp) < 0) {
		usb_autopm_put_interface(intf);
		usblp->used = 0;
		file->private_data = NULL;
		retval = -EIO;
	}
out:
	mutex_unlock (&usblp_mutex);
	return retval;
}