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
struct usb_interface_cache {int /*<<< orphan*/  ref; } ;
struct usb_interface {int /*<<< orphan*/  altsetting; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb_interface_cache* altsetting_to_usb_interface_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  usb_release_interface_cache ; 

__attribute__((used)) static void usb_release_interface(struct device *dev)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_interface_cache *intfc =
			altsetting_to_usb_interface_cache(intf->altsetting);

	kref_put(&intfc->ref, usb_release_interface_cache);
	kfree(intf);
}