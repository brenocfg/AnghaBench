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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct hda_codec {struct cmi_spec* spec; } ;
struct cmi_spec {int /*<<< orphan*/  num_channel_modes; int /*<<< orphan*/  channel_modes; } ;

/* Variables and functions */
 int snd_hda_ch_mode_info (struct hda_codec*,struct snd_ctl_elem_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int cmi_ch_mode_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct cmi_spec *spec = codec->spec;
	return snd_hda_ch_mode_info(codec, uinfo, spec->channel_modes,
				    spec->num_channel_modes);
}