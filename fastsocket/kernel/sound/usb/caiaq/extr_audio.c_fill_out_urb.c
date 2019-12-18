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
struct usb_iso_packet_descriptor {int dummy; } ;
struct urb {int dummy; } ;
struct TYPE_2__ {int data_alignment; } ;
struct snd_usb_caiaqdev {TYPE_1__ spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_out_urb_mode_0 (struct snd_usb_caiaqdev*,struct urb*,struct usb_iso_packet_descriptor const*) ; 
 int /*<<< orphan*/  fill_out_urb_mode_3 (struct snd_usb_caiaqdev*,struct urb*,struct usb_iso_packet_descriptor const*) ; 

__attribute__((used)) static inline void fill_out_urb(struct snd_usb_caiaqdev *dev,
				struct urb *urb,
				const struct usb_iso_packet_descriptor *iso)
{
	switch (dev->spec.data_alignment) {
	case 0:
	case 2:
		fill_out_urb_mode_0(dev, urb, iso);
		break;
	case 3:
		fill_out_urb_mode_3(dev, urb, iso);
		break;
	}
}