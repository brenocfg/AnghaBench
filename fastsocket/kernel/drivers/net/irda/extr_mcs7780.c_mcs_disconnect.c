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
struct mcs_cb {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRDA_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 struct mcs_cb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcs_disconnect(struct usb_interface *intf)
{
	struct mcs_cb *mcs = usb_get_intfdata(intf);

	if (!mcs)
		return;

	flush_scheduled_work();

	unregister_netdev(mcs->netdev);
	free_netdev(mcs->netdev);

	usb_set_intfdata(intf, NULL);
	IRDA_DEBUG(0, "MCS7780 now disconnected.\n");
}