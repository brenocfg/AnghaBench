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
struct urb {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  tx_cmd_urbs; int /*<<< orphan*/  tx_anch; int /*<<< orphan*/  tx_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int carl9170_usb_submit_cmd_urb(struct ar9170 *ar)
{
	struct urb *urb;
	int err;

	if (atomic_inc_return(&ar->tx_cmd_urbs) != 1) {
		atomic_dec(&ar->tx_cmd_urbs);
		return 0;
	}

	urb = usb_get_from_anchor(&ar->tx_cmd);
	if (!urb) {
		atomic_dec(&ar->tx_cmd_urbs);
		return 0;
	}

	usb_anchor_urb(urb, &ar->tx_anch);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(err)) {
		usb_unanchor_urb(urb);
		atomic_dec(&ar->tx_cmd_urbs);
	}
	usb_free_urb(urb);

	return err;
}