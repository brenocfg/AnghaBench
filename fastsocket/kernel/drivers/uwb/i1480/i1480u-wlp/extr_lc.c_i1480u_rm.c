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
struct uwb_rc {int dummy; } ;
struct TYPE_2__ {struct uwb_rc* rc; } ;
struct i1480u {int /*<<< orphan*/  usb_dev; TYPE_1__ wlp; int /*<<< orphan*/  notif_urb; int /*<<< orphan*/  usb_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  wlp_remove (TYPE_1__*) ; 

__attribute__((used)) static void i1480u_rm(struct i1480u *i1480u)
{
	struct uwb_rc *rc = i1480u->wlp.rc;
	usb_set_intfdata(i1480u->usb_iface, NULL);
#ifdef i1480u_FLOW_CONTROL
	usb_kill_urb(i1480u->notif_urb);
	usb_free_urb(i1480u->notif_urb);
#endif
	wlp_remove(&i1480u->wlp);
	uwb_rc_put(rc);
	usb_put_dev(i1480u->usb_dev);
}