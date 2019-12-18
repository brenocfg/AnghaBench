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
struct zd_usb {int /*<<< orphan*/  submitted_cmds; int /*<<< orphan*/  intf; } ;
struct usb_interface {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_usb_interrupt (struct zd_usb*) ; 
 int /*<<< orphan*/  init_usb_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  init_usb_tx (struct zd_usb*) ; 
 int /*<<< orphan*/  memset (struct zd_usb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,struct ieee80211_hw*) ; 

void zd_usb_init(struct zd_usb *usb, struct ieee80211_hw *hw,
	         struct usb_interface *intf)
{
	memset(usb, 0, sizeof(*usb));
	usb->intf = usb_get_intf(intf);
	usb_set_intfdata(usb->intf, hw);
	init_usb_anchor(&usb->submitted_cmds);
	init_usb_interrupt(usb);
	init_usb_tx(usb);
	init_usb_rx(usb);
}