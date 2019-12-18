#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_mixer_interface {scalar_t__ chip; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ftu_eff_switch_priv_val {int cached_value; int is_cached; scalar_t__ mixer; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UAC_GET_CUR ; 
 int /*<<< orphan*/  UAC_SET_CUR ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,int const,unsigned char*,int const) ; 
 int const snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ftu_eff_switch_put(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_usb_audio *chip;
	struct snd_ftu_eff_switch_priv_val *pval;

	struct usb_mixer_interface *mixer;
	int changed, cur_val, err, new_val;
	unsigned char value[2];


	const int id = 6;
	const int validx = 1;
	const int val_len = 2;

	changed = 0;

	pval = (struct snd_ftu_eff_switch_priv_val *)
		kctl->private_value;
	cur_val = pval->cached_value;
	new_val = ucontrol->value.enumerated.item[0];

	mixer = (struct usb_mixer_interface *) pval->mixer;
	if (snd_BUG_ON(!mixer))
		return -EINVAL;

	chip = (struct snd_usb_audio *) mixer->chip;
	if (snd_BUG_ON(!chip))
		return -EINVAL;

	if (!pval->is_cached) {
		/* Read current value */
		err = snd_usb_ctl_msg(chip->dev,
				usb_rcvctrlpipe(chip->dev, 0), UAC_GET_CUR,
				USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
				validx << 8, snd_usb_ctrl_intf(chip) | (id << 8),
				value, val_len);
		if (err < 0)
			return err;

		cur_val = value[0];
		pval->cached_value = cur_val;
		pval->is_cached = 1;
	}
	/* update value if needed */
	if (cur_val != new_val) {
		value[0] = new_val;
		value[1] = 0;
		err = snd_usb_ctl_msg(chip->dev,
				usb_sndctrlpipe(chip->dev, 0), UAC_SET_CUR,
				USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_OUT,
				validx << 8, snd_usb_ctrl_intf(chip) | (id << 8),
				value, val_len);
		if (err < 0)
			return err;

		pval->cached_value = new_val;
		pval->is_cached = 1;
		changed = 1;
	}

	return changed;
}