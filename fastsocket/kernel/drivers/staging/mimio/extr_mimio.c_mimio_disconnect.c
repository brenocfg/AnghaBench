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
struct usb_interface {int dummy; } ;
struct mimio {scalar_t__ open; scalar_t__ present; TYPE_1__* idev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disconnect_sem ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mimio_dealloc (struct mimio*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 struct mimio* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mimio_disconnect(struct usb_interface *ifc)
{
	struct mimio *mimio;

	down(&disconnect_sem);

	mimio = usb_get_intfdata(ifc);
	usb_set_intfdata(ifc, NULL);
	dev_dbg(&mimio->idev->dev, "disconnect\n");

	if (mimio) {
		mimio->present = 0;

		if (mimio->open <= 0)
			mimio_dealloc(mimio);
	}

	up(&disconnect_sem);
}