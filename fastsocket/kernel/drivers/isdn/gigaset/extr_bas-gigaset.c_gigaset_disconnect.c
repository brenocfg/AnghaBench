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
struct TYPE_2__ {struct bas_cardstate* bas; } ;
struct cardstate {int /*<<< orphan*/ * dev; scalar_t__ bcs; TYPE_1__ hw; } ;
struct bas_cardstate {int /*<<< orphan*/ * udev; int /*<<< orphan*/ * interface; scalar_t__ rcvbuf_size; int /*<<< orphan*/ * rcvbuf; int /*<<< orphan*/  timer_cmd_in; int /*<<< orphan*/  timer_atrdy; int /*<<< orphan*/  timer_ctrl; scalar_t__ basstate; } ;

/* Variables and functions */
 int BAS_CHANNELS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  freeurbs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_bchannel_down (scalar_t__) ; 
 int /*<<< orphan*/  gigaset_freecs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_stop (struct cardstate*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct cardstate* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gigaset_disconnect(struct usb_interface *interface)
{
	struct cardstate *cs;
	struct bas_cardstate *ucs;
	int j;

	cs = usb_get_intfdata(interface);

	ucs = cs->hw.bas;

	dev_info(cs->dev, "disconnecting Gigaset base\n");

	/* mark base as not ready, all channels disconnected */
	ucs->basstate = 0;

	/* tell LL all channels are down */
	for (j = 0; j < BAS_CHANNELS; ++j)
		gigaset_bchannel_down(cs->bcs + j);

	/* stop driver (common part) */
	gigaset_stop(cs);

	/* stop timers and URBs, free ressources */
	del_timer_sync(&ucs->timer_ctrl);
	del_timer_sync(&ucs->timer_atrdy);
	del_timer_sync(&ucs->timer_cmd_in);
	freeurbs(cs);
	usb_set_intfdata(interface, NULL);
	kfree(ucs->rcvbuf);
	ucs->rcvbuf = NULL;
	ucs->rcvbuf_size = 0;
	usb_put_dev(ucs->udev);
	ucs->interface = NULL;
	ucs->udev = NULL;
	cs->dev = NULL;
	gigaset_freecs(cs);
}