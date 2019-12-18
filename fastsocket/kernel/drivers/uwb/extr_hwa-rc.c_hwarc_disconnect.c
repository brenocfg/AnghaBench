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
struct uwb_rc {int dummy; } ;
struct usb_interface {int dummy; } ;
struct hwarc {int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  usb_iface; struct uwb_rc* uwb_rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hwarc*) ; 
 struct hwarc* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_rm (struct uwb_rc*) ; 

__attribute__((used)) static void hwarc_disconnect(struct usb_interface *iface)
{
	struct hwarc *hwarc = usb_get_intfdata(iface);
	struct uwb_rc *uwb_rc = hwarc->uwb_rc;

	usb_set_intfdata(hwarc->usb_iface, NULL);
	uwb_rc_rm(uwb_rc);
	usb_put_intf(hwarc->usb_iface);
	usb_put_dev(hwarc->usb_dev);
	kfree(hwarc);
	uwb_rc_put(uwb_rc);	/* when creating the device, refcount = 1 */
}