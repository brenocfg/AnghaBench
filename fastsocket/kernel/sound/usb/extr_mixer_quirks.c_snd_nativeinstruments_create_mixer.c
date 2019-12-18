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
struct usb_mixer_interface {TYPE_1__* chip; } ;
struct snd_kcontrol_new {int /*<<< orphan*/  private_value; int /*<<< orphan*/  name; int /*<<< orphan*/  info; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_boolean_mono_info ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct usb_mixer_interface*) ; 
 int /*<<< orphan*/  snd_nativeinstruments_control_get ; 
 int /*<<< orphan*/  snd_nativeinstruments_control_put ; 

__attribute__((used)) static int snd_nativeinstruments_create_mixer(struct usb_mixer_interface *mixer,
					      const struct snd_kcontrol_new *kc,
					      unsigned int count)
{
	int i, err = 0;
	struct snd_kcontrol_new template = {
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.get = snd_nativeinstruments_control_get,
		.put = snd_nativeinstruments_control_put,
		.info = snd_ctl_boolean_mono_info,
	};

	for (i = 0; i < count; i++) {
		struct snd_kcontrol *c;

		template.name = kc[i].name;
		template.private_value = kc[i].private_value;

		c = snd_ctl_new1(&template, mixer);
		err = snd_ctl_add(mixer->chip->card, c);

		if (err < 0)
			break;
	}

	return err;
}