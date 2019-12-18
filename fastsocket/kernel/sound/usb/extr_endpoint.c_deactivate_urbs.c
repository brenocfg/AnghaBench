#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int dummy; } ;
struct snd_usb_endpoint {unsigned int nurbs; TYPE_2__* urb; int /*<<< orphan*/  unlink_mask; int /*<<< orphan*/  active_mask; scalar_t__ next_packet_write_pos; scalar_t__ next_packet_read_pos; int /*<<< orphan*/  ready_playback_urbs; int /*<<< orphan*/  flags; TYPE_1__* chip; } ;
struct TYPE_4__ {struct urb* urb; } ;
struct TYPE_3__ {scalar_t__ async_unlink; scalar_t__ shutdown; } ;

/* Variables and functions */
 int EBADFD ; 
 int /*<<< orphan*/  EP_FLAG_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

__attribute__((used)) static int deactivate_urbs(struct snd_usb_endpoint *ep, int force, int can_sleep)
{
	unsigned int i;
	int async;

	if (!force && ep->chip->shutdown) /* to be sure... */
		return -EBADFD;

	async = !can_sleep && ep->chip->async_unlink;

	clear_bit(EP_FLAG_RUNNING, &ep->flags);

	INIT_LIST_HEAD(&ep->ready_playback_urbs);
	ep->next_packet_read_pos = 0;
	ep->next_packet_write_pos = 0;

	if (!async && in_interrupt())
		return 0;

	for (i = 0; i < ep->nurbs; i++) {
		if (test_bit(i, &ep->active_mask)) {
			if (!test_and_set_bit(i, &ep->unlink_mask)) {
				struct urb *u = ep->urb[i].urb;
				if (async)
					usb_unlink_urb(u);
				else
					usb_kill_urb(u);
			}
		}
	}

	return 0;
}