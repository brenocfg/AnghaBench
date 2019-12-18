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
struct usb_interface_descriptor {int bInterfaceProtocol; } ;
struct usb_host_interface {int dummy; } ;
struct snd_usb_audio {int dummy; } ;
struct audioformat {int attributes; } ;

/* Variables and functions */
 int UAC_EP_CS_ATTR_PITCH_CONTROL ; 
#define  UAC_VERSION_1 129 
#define  UAC_VERSION_2 128 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int init_pitch_v1 (struct snd_usb_audio*,int,struct usb_host_interface*,struct audioformat*) ; 
 int init_pitch_v2 (struct snd_usb_audio*,int,struct usb_host_interface*,struct audioformat*) ; 

int snd_usb_init_pitch(struct snd_usb_audio *chip, int iface,
		       struct usb_host_interface *alts,
		       struct audioformat *fmt)
{
	struct usb_interface_descriptor *altsd = get_iface_desc(alts);

	/* if endpoint doesn't have pitch control, bail out */
	if (!(fmt->attributes & UAC_EP_CS_ATTR_PITCH_CONTROL))
		return 0;

	switch (altsd->bInterfaceProtocol) {
	case UAC_VERSION_1:
	default:
		return init_pitch_v1(chip, iface, alts, fmt);

	case UAC_VERSION_2:
		return init_pitch_v2(chip, iface, alts, fmt);
	}
}