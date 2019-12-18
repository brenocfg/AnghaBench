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
struct usbmix_name_map {TYPE_1__* dB; } ;
struct usb_mixer_elem_info {int initialized; int /*<<< orphan*/  dBmax; int /*<<< orphan*/  dBmin; } ;
struct TYPE_2__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */

__attribute__((used)) static inline void check_mapped_dB(const struct usbmix_name_map *p,
				   struct usb_mixer_elem_info *cval)
{
	if (p && p->dB) {
		cval->dBmin = p->dB->min;
		cval->dBmax = p->dB->max;
		cval->initialized = 1;
	}
}