#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  status; } ;
struct ar9170 {int /*<<< orphan*/  tx_anch_urbs; int /*<<< orphan*/  tx_err; TYPE_1__* udev; int /*<<< orphan*/  tx_anch; int /*<<< orphan*/  tx_wait; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AR9170_NUM_TX_URBS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void carl9170_usb_submit_data_urb(struct ar9170 *ar)
{
	struct urb *urb;
	int err;

	if (atomic_inc_return(&ar->tx_anch_urbs) > AR9170_NUM_TX_URBS)
		goto err_acc;

	urb = usb_get_from_anchor(&ar->tx_wait);
	if (!urb)
		goto err_acc;

	usb_anchor_urb(urb, &ar->tx_anch);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(err)) {
		if (net_ratelimit()) {
			dev_err(&ar->udev->dev, "tx submit failed (%d)\n",
				urb->status);
		}

		usb_unanchor_urb(urb);
		usb_anchor_urb(urb, &ar->tx_err);
	}

	usb_free_urb(urb);

	if (likely(err == 0))
		return;

err_acc:
	atomic_dec(&ar->tx_anch_urbs);
}