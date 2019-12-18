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
struct usb_mixer_interface {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int USB_MIXER_S16 ; 
 int snd_create_std_mono_ctl (struct usb_mixer_interface*,unsigned int const,unsigned int const,unsigned int,int const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_mixer_vol_tlv ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int snd_ftu_create_effect_return_ctls(struct usb_mixer_interface *mixer)
{
	unsigned int cmask;
	int err, ch;
	char name[48];

	const unsigned int id = 7;
	const int val_type = USB_MIXER_S16;
	const unsigned int control = 7;

	for (ch = 0; ch < 4; ++ch) {
		cmask = 1 << ch;
		snprintf(name, sizeof(name),
			"Effect Return %d Volume", ch + 1);
		err = snd_create_std_mono_ctl(mixer, id, control,
						cmask, val_type, name,
						snd_usb_mixer_vol_tlv);
		if (err < 0)
			return err;
	}

	return 0;
}