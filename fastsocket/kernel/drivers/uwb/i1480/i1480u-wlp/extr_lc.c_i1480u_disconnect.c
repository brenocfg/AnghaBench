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
struct net_device {int dummy; } ;
struct i1480u {int /*<<< orphan*/  notif_urb; struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  i1480u_rm (struct i1480u*) ; 
 int /*<<< orphan*/  i1480u_sysfs_release (struct i1480u*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct i1480u* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i1480u_disconnect(struct usb_interface *iface)
{
	struct i1480u *i1480u;
	struct net_device *net_dev;

	i1480u = usb_get_intfdata(iface);
	net_dev = i1480u->net_dev;
	netif_stop_queue(net_dev);
#ifdef i1480u_FLOW_CONTROL
	usb_kill_urb(i1480u->notif_urb);
#endif
	i1480u_sysfs_release(i1480u);
	unregister_netdev(net_dev);
	i1480u_rm(i1480u);
	free_netdev(net_dev);
}