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
struct snd_usb_endpoint {scalar_t__ use_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EP_FLAG_ACTIVATED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deactivate_urbs (struct snd_usb_endpoint*,int,int) ; 
 int /*<<< orphan*/  wait_clear_urbs (struct snd_usb_endpoint*) ; 

int snd_usb_endpoint_deactivate(struct snd_usb_endpoint *ep)
{
	if (!ep)
		return -EINVAL;

	deactivate_urbs(ep, 1, 1);
	wait_clear_urbs(ep);

	if (ep->use_count != 0)
		return 0;

	clear_bit(EP_FLAG_ACTIVATED, &ep->flags);

	return 0;
}