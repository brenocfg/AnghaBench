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
struct kingsun_cb {int /*<<< orphan*/  netdev; int /*<<< orphan*/  in_buf; int /*<<< orphan*/  out_buf; int /*<<< orphan*/ * rx_urb; int /*<<< orphan*/ * tx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 struct kingsun_cb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kingsun_disconnect(struct usb_interface *intf)
{
	struct kingsun_cb *kingsun = usb_get_intfdata(intf);

	if (!kingsun)
		return;

	unregister_netdev(kingsun->netdev);

	/* Mop up receive && transmit urb's */
	if (kingsun->tx_urb != NULL) {
		usb_kill_urb(kingsun->tx_urb);
		usb_free_urb(kingsun->tx_urb);
		kingsun->tx_urb = NULL;
	}
	if (kingsun->rx_urb != NULL) {
		usb_kill_urb(kingsun->rx_urb);
		usb_free_urb(kingsun->rx_urb);
		kingsun->rx_urb = NULL;
	}

	kfree(kingsun->out_buf);
	kfree(kingsun->in_buf);
	free_netdev(kingsun->netdev);

	usb_set_intfdata(intf, NULL);
}