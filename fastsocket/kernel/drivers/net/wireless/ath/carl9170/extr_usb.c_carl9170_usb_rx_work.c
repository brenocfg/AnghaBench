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
struct urb {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; } ;
struct ar9170 {int /*<<< orphan*/  rx_pool_urbs; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  rx_work_urbs; int /*<<< orphan*/  rx_work; } ;

/* Variables and functions */
 int AR9170_NUM_RX_URBS_POOL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_INITIALIZED (struct ar9170*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_rx (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_usb_submit_rx_urb (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carl9170_usb_rx_work(struct ar9170 *ar)
{
	struct urb *urb;
	int i;

	for (i = 0; i < AR9170_NUM_RX_URBS_POOL; i++) {
		urb = usb_get_from_anchor(&ar->rx_work);
		if (!urb)
			break;

		atomic_dec(&ar->rx_work_urbs);
		if (IS_INITIALIZED(ar)) {
			carl9170_rx(ar, urb->transfer_buffer,
				    urb->actual_length);
		}

		usb_anchor_urb(urb, &ar->rx_pool);
		atomic_inc(&ar->rx_pool_urbs);

		usb_free_urb(urb);

		carl9170_usb_submit_rx_urb(ar, GFP_ATOMIC);
	}
}