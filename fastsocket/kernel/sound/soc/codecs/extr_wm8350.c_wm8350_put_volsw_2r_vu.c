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
typedef  int u16 ;
struct wm8350_output {int /*<<< orphan*/  active; int /*<<< orphan*/  right_vol; int /*<<< orphan*/  left_vol; } ;
struct wm8350_data {struct wm8350_output out2; struct wm8350_output out1; } ;
struct soc_mixer_control {unsigned int reg; } ;
struct snd_soc_codec {struct wm8350_data* private_data; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
#define  WM8350_LOUT1_VOLUME 129 
#define  WM8350_LOUT2_VOLUME 128 
 int WM8350_OUT1_VU ; 
 struct snd_soc_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw_2r (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int wm8350_codec_read (struct snd_soc_codec*,unsigned int) ; 
 int /*<<< orphan*/  wm8350_codec_write (struct snd_soc_codec*,unsigned int,int) ; 

__attribute__((used)) static int wm8350_put_volsw_2r_vu(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct wm8350_data *wm8350_priv = codec->private_data;
	struct wm8350_output *out = NULL;
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	int ret;
	unsigned int reg = mc->reg;
	u16 val;

	/* For OUT1 and OUT2 we shadow the values and only actually write
	 * them out when active in order to ensure the amplifier comes on
	 * as quietly as possible. */
	switch (reg) {
	case WM8350_LOUT1_VOLUME:
		out = &wm8350_priv->out1;
		break;
	case WM8350_LOUT2_VOLUME:
		out = &wm8350_priv->out2;
		break;
	default:
		break;
	}

	if (out) {
		out->left_vol = ucontrol->value.integer.value[0];
		out->right_vol = ucontrol->value.integer.value[1];
		if (!out->active)
			return 1;
	}

	ret = snd_soc_put_volsw_2r(kcontrol, ucontrol);
	if (ret < 0)
		return ret;

	/* now hit the volume update bits (always bit 8) */
	val = wm8350_codec_read(codec, reg);
	wm8350_codec_write(codec, reg, val | WM8350_OUT1_VU);
	return 1;
}