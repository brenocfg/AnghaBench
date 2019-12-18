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
struct if_usb_card {int /*<<< orphan*/ * ep_out_buf; int /*<<< orphan*/ * cmd_urb; int /*<<< orphan*/ * rx_urb; int /*<<< orphan*/ * tx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_USB ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_usb_free(struct if_usb_card *cardp)
{
	lbtf_deb_enter(LBTF_DEB_USB);

	/* Unlink tx & rx urb */
	usb_kill_urb(cardp->tx_urb);
	usb_kill_urb(cardp->rx_urb);
	usb_kill_urb(cardp->cmd_urb);

	usb_free_urb(cardp->tx_urb);
	cardp->tx_urb = NULL;

	usb_free_urb(cardp->rx_urb);
	cardp->rx_urb = NULL;

	usb_free_urb(cardp->cmd_urb);
	cardp->cmd_urb = NULL;

	kfree(cardp->ep_out_buf);
	cardp->ep_out_buf = NULL;

	lbtf_deb_leave(LBTF_DEB_USB);
}