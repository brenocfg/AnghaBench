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
struct usblp {scalar_t__ sleeping; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int handle_bidir (struct usblp*) ; 
 struct usblp* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int usblp_resume (struct usb_interface *intf)
{
	struct usblp *usblp = usb_get_intfdata (intf);
	int r;

	usblp->sleeping = 0;
	r = handle_bidir (usblp);

	return r;
}