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
struct usblp {int /*<<< orphan*/  intf; scalar_t__ present; scalar_t__ used; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct file {struct usblp* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP_ABORT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usblp_cleanup (struct usblp*) ; 
 int /*<<< orphan*/  usblp_mutex ; 
 int /*<<< orphan*/  usblp_unlink_urbs (struct usblp*) ; 

__attribute__((used)) static int usblp_release(struct inode *inode, struct file *file)
{
	struct usblp *usblp = file->private_data;

	usblp->flags &= ~LP_ABORT;

	mutex_lock (&usblp_mutex);
	usblp->used = 0;
	if (usblp->present) {
		usblp_unlink_urbs(usblp);
		usb_autopm_put_interface(usblp->intf);
	} else 		/* finish cleanup from disconnect */
		usblp_cleanup (usblp);
	mutex_unlock (&usblp_mutex);
	return 0;
}