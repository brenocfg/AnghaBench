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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct alauda {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  alauda_delete ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct alauda* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alauda_disconnect(struct usb_interface *interface)
{
	struct alauda *al;

	al = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	/* FIXME: prevent more I/O from starting */

	/* decrement our usage count */
	if (al)
		kref_put(&al->kref, alauda_delete);

	dev_info(&interface->dev, "alauda gone");
}