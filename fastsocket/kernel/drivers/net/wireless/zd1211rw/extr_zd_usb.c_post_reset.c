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
struct zd_usb {scalar_t__ was_running; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; struct zd_usb usb; } ;
struct zd_mac {TYPE_1__ chip; } ;
struct usb_interface {scalar_t__ condition; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_INTERFACE_BOUND ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  zd_usb_resume (struct zd_usb*) ; 

__attribute__((used)) static int post_reset(struct usb_interface *intf)
{
	struct ieee80211_hw *hw = usb_get_intfdata(intf);
	struct zd_mac *mac;
	struct zd_usb *usb;

	if (!hw || intf->condition != USB_INTERFACE_BOUND)
		return 0;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	mutex_unlock(&mac->chip.mutex);

	if (usb->was_running)
		zd_usb_resume(usb);
	return 0;
}