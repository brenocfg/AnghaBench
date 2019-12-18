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
struct wdm_device {int /*<<< orphan*/  plock; TYPE_1__* intf; } ;
struct usb_interface {int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int recover_from_urb_loss (struct wdm_device*) ; 
 struct wdm_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int wdm_resume(struct usb_interface *intf)
{
	struct wdm_device *desc = usb_get_intfdata(intf);
	int rv;

	dev_dbg(&desc->intf->dev, "wdm%d_resume\n", intf->minor);
	mutex_lock(&desc->plock);
	rv = recover_from_urb_loss(desc);
	mutex_unlock(&desc->plock);
	return rv;
}