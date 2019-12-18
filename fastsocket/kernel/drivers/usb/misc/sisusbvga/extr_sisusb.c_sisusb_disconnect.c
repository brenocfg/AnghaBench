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
struct usb_interface {int dummy; } ;
struct sisusb_usb_data {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; scalar_t__ ready; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_console_exit (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_delete ; 
 int /*<<< orphan*/  sisusb_kill_all_busy (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_wait_all_out_complete (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sisusb_class ; 

__attribute__((used)) static void sisusb_disconnect(struct usb_interface *intf)
{
	struct sisusb_usb_data *sisusb;

	/* This should *not* happen */
	if (!(sisusb = usb_get_intfdata(intf)))
		return;

#ifdef INCL_SISUSB_CON
	sisusb_console_exit(sisusb);
#endif

	usb_deregister_dev(intf, &usb_sisusb_class);

	mutex_lock(&sisusb->lock);

	/* Wait for all URBs to complete and kill them in case (MUST do) */
	if (!sisusb_wait_all_out_complete(sisusb))
		sisusb_kill_all_busy(sisusb);

	usb_set_intfdata(intf, NULL);

	sisusb->present = 0;
	sisusb->ready = 0;

	mutex_unlock(&sisusb->lock);

	/* decrement our usage count */
	kref_put(&sisusb->kref, sisusb_delete);
}