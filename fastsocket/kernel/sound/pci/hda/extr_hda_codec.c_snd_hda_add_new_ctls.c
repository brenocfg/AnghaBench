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
struct snd_kcontrol_new {int iface; scalar_t__ name; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int device; int index; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct hda_codec {int addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int find_empty_mixer_ctl_idx (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new const*,struct hda_codec*) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 

int snd_hda_add_new_ctls(struct hda_codec *codec,
			 const struct snd_kcontrol_new *knew)
{
	int err;

	for (; knew->name; knew++) {
		struct snd_kcontrol *kctl;
		int addr = 0, idx = 0;
		if (knew->iface == -1)	/* skip this codec private value */
			continue;
		for (;;) {
			kctl = snd_ctl_new1(knew, codec);
			if (!kctl)
				return -ENOMEM;
			if (addr > 0)
				kctl->id.device = addr;
			if (idx > 0)
				kctl->id.index = idx;
			err = snd_hda_ctl_add(codec, 0, kctl);
			if (!err)
				break;
			/* try first with another device index corresponding to
			 * the codec addr; if it still fails (or it's the
			 * primary codec), then try another control index
			 */
			if (!addr && codec->addr)
				addr = codec->addr;
			else if (!idx && !knew->index) {
				idx = find_empty_mixer_ctl_idx(codec,
							       knew->name, 0);
				if (idx <= 0)
					return err;
			} else
				return err;
		}
	}
	return 0;
}