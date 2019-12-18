#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct usb_interface {int dummy; } ;
typedef  TYPE_1__* pdabusb_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int remove_pending; scalar_t__ state; scalar_t__ overruns; int /*<<< orphan*/ * usbdev; int /*<<< orphan*/  remove_ok; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ _started ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dabusb_class ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dabusb_disconnect (struct usb_interface *intf)
{
	wait_queue_t __wait;
	pdabusb_t s = usb_get_intfdata (intf);

	dbg("dabusb_disconnect");

	init_waitqueue_entry(&__wait, current);

	usb_set_intfdata (intf, NULL);
	if (s) {
		usb_deregister_dev (intf, &dabusb_class);
		s->remove_pending = 1;
		wake_up (&s->wait);
		add_wait_queue(&s->remove_ok, &__wait);
		set_current_state(TASK_UNINTERRUPTIBLE);
		if (s->state == _started)
			schedule();
		current->state = TASK_RUNNING;
		remove_wait_queue(&s->remove_ok, &__wait);

		s->usbdev = NULL;
		s->overruns = 0;
	}
}