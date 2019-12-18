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
struct snd_usb_endpoint {scalar_t__ use_count; int /*<<< orphan*/ * prepare_data_urb; int /*<<< orphan*/ * retire_data_urb; int /*<<< orphan*/ * sync_slave; int /*<<< orphan*/ * data_subs; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_urbs (struct snd_usb_endpoint*,int,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  wait_clear_urbs (struct snd_usb_endpoint*) ; 

void snd_usb_endpoint_stop(struct snd_usb_endpoint *ep,
			   int force, int can_sleep, int wait)
{
	if (!ep)
		return;

	if (snd_BUG_ON(ep->use_count == 0))
		return;

	if (--ep->use_count == 0) {
		deactivate_urbs(ep, force, can_sleep);
		ep->data_subs = NULL;
		ep->sync_slave = NULL;
		ep->retire_data_urb = NULL;
		ep->prepare_data_urb = NULL;

		if (wait)
			wait_clear_urbs(ep);
	}
}