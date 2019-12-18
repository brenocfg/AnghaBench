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
struct usb_hub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUB_PRE_RESET ; 
 int /*<<< orphan*/  hub_quiesce (struct usb_hub*,int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int hub_pre_reset(struct usb_interface *intf)
{
	struct usb_hub *hub = usb_get_intfdata(intf);

	hub_quiesce(hub, HUB_PRE_RESET);
	return 0;
}