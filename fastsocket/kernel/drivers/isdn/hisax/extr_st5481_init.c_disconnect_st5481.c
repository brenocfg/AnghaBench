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
struct st5481_adapter {int /*<<< orphan*/  hisax_d_if; int /*<<< orphan*/ * bcs; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  hisax_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct st5481_adapter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  st5481_release_b (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5481_release_d (struct st5481_adapter*) ; 
 int /*<<< orphan*/  st5481_release_usb (struct st5481_adapter*) ; 
 int /*<<< orphan*/  st5481_stop (struct st5481_adapter*) ; 
 struct st5481_adapter* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disconnect_st5481(struct usb_interface *intf)
{
	struct st5481_adapter *adapter = usb_get_intfdata(intf);

	DBG(1,"");

	usb_set_intfdata(intf, NULL);
	if (!adapter)
		return;
	
	list_del(&adapter->list);

	st5481_stop(adapter);
	st5481_release_b(&adapter->bcs[1]);
	st5481_release_b(&adapter->bcs[0]);
	st5481_release_d(adapter);
	// we would actually better wait for completion of outstanding urbs
	mdelay(2);
	st5481_release_usb(adapter);

	hisax_unregister(&adapter->hisax_d_if);

	kfree(adapter);
}