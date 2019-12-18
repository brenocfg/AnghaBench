#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acm {int rx_buflimit; TYPE_3__* control; TYPE_2__* ru; TYPE_1__* wb; int /*<<< orphan*/  ctrlurb; scalar_t__ dev; int /*<<< orphan*/  drain_wait; scalar_t__ ctrlout; } ;
struct TYPE_7__ {scalar_t__ needs_remote_wakeup; } ;
struct TYPE_6__ {int /*<<< orphan*/  urb; } ;
struct TYPE_5__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ACM_CLOSE_TIMEOUT ; 
 int ACM_NW ; 
 int HZ ; 
 int /*<<< orphan*/  acm_set_control (struct acm*,scalar_t__) ; 
 int acm_wb_is_avail (struct acm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_mutex ; 
 int /*<<< orphan*/  usb_autopm_get_interface (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void acm_port_down(struct acm *acm, int drain)
{
	int i, nr = acm->rx_buflimit;
	mutex_lock(&open_mutex);
	if (acm->dev) {
		usb_autopm_get_interface(acm->control);
		acm_set_control(acm, acm->ctrlout = 0);
		/* try letting the last writes drain naturally */
		if (drain) {
			wait_event_interruptible_timeout(acm->drain_wait,
				(ACM_NW == acm_wb_is_avail(acm)) || !acm->dev,
					ACM_CLOSE_TIMEOUT * HZ);
		}
		usb_kill_urb(acm->ctrlurb);
		for (i = 0; i < ACM_NW; i++)
			usb_kill_urb(acm->wb[i].urb);
		for (i = 0; i < nr; i++)
			usb_kill_urb(acm->ru[i].urb);
		acm->control->needs_remote_wakeup = 0;
		usb_autopm_put_interface(acm->control);
	}
	mutex_unlock(&open_mutex);
}