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
struct irda_usb_cb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int irda_usb_is_receiving(struct irda_usb_cb *self)
{
	/* Note : because of the way UHCI works, it's almost impossible
	 * to get this info. The Controller DMA directly to memory and
	 * signal only when the whole frame is finished. To know if the
	 * first TD of the URB has been filled or not seems hard work...
	 *
	 * The other solution would be to use the "receiving" command
	 * on the default decriptor with a usb_control_msg(), but that
	 * would add USB traffic and would return result only in the
	 * next USB frame (~1ms).
	 *
	 * I've been told that current dongles send status info on their
	 * interrupt endpoint, and that's what the Windows driver uses
	 * to know this info. Unfortunately, this is not yet in the spec...
	 *
	 * Jean II
	 */

	return 0; /* For now */
}