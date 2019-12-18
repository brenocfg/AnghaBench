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
struct usb_host_interface {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;
struct uac_clock_selector_descriptor {int bClockID; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC2_CLOCK_SELECTOR ; 
 struct uac_clock_selector_descriptor* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uac_clock_selector_descriptor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct uac_clock_selector_descriptor *
	snd_usb_find_clock_selector(struct usb_host_interface *ctrl_iface,
				    int clock_id)
{
	struct uac_clock_selector_descriptor *cs = NULL;

	while ((cs = snd_usb_find_csint_desc(ctrl_iface->extra,
					     ctrl_iface->extralen,
					     cs, UAC2_CLOCK_SELECTOR))) {
		if (cs->bClockID == clock_id)
			return cs;
	}

	return NULL;
}