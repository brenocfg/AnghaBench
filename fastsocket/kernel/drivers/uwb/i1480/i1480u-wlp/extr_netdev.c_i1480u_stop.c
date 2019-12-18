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
struct wlp {int /*<<< orphan*/  pal; int /*<<< orphan*/  wss; int /*<<< orphan*/ * rc; } ;
struct net_device {int dummy; } ;
struct i1480u {int /*<<< orphan*/  notif_urb; struct wlp wlp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i1480u_rx_release (struct i1480u*) ; 
 int /*<<< orphan*/  i1480u_tx_release (struct i1480u*) ; 
 struct i1480u* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_radio_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_wss_remove (int /*<<< orphan*/ *) ; 

int i1480u_stop(struct net_device *net_dev)
{
	struct i1480u *i1480u = netdev_priv(net_dev);
	struct wlp *wlp = &i1480u->wlp;

	BUG_ON(wlp->rc == NULL);
	wlp_wss_remove(&wlp->wss);
	netif_carrier_off(net_dev);
#ifdef i1480u_FLOW_CONTROL
	usb_kill_urb(i1480u->notif_urb);
#endif
	netif_stop_queue(net_dev);
	uwb_radio_stop(&wlp->pal);
	i1480u_rx_release(i1480u);
	i1480u_tx_release(i1480u);
	return 0;
}