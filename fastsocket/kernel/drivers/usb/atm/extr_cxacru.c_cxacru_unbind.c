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
struct usbatm_data {struct cxacru_data* driver_data; } ;
struct usb_interface {int dummy; } ;
struct cxacru_data {scalar_t__ poll_state; scalar_t__ rcv_buf; scalar_t__ snd_buf; int /*<<< orphan*/  rcv_urb; int /*<<< orphan*/  snd_urb; int /*<<< orphan*/  poll_work; int /*<<< orphan*/  poll_state_serialize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CXPOLL_SHUTDOWN ; 
 scalar_t__ CXPOLL_STOPPED ; 
 int /*<<< orphan*/  cancel_rearming_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct cxacru_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxacru_unbind(struct usbatm_data *usbatm_instance,
		struct usb_interface *intf)
{
	struct cxacru_data *instance = usbatm_instance->driver_data;
	int is_polling = 1;

	dbg("cxacru_unbind entered");

	if (!instance) {
		dbg("cxacru_unbind: NULL instance!");
		return;
	}

	mutex_lock(&instance->poll_state_serialize);
	BUG_ON(instance->poll_state == CXPOLL_SHUTDOWN);

	/* ensure that status polling continues unless
	 * it has already stopped */
	if (instance->poll_state == CXPOLL_STOPPED)
		is_polling = 0;

	/* stop polling from being stopped or started */
	instance->poll_state = CXPOLL_SHUTDOWN;
	mutex_unlock(&instance->poll_state_serialize);

	if (is_polling)
		cancel_rearming_delayed_work(&instance->poll_work);

	usb_kill_urb(instance->snd_urb);
	usb_kill_urb(instance->rcv_urb);
	usb_free_urb(instance->snd_urb);
	usb_free_urb(instance->rcv_urb);

	free_page((unsigned long) instance->snd_buf);
	free_page((unsigned long) instance->rcv_buf);

	kfree(instance);

	usbatm_instance->driver_data = NULL;
}