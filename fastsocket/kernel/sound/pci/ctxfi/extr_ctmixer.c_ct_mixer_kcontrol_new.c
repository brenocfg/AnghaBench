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
struct snd_kcontrol_new {int private_value; } ;
struct TYPE_3__ {scalar_t__ iface; int /*<<< orphan*/  device; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct ct_mixer {TYPE_2__* atc; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IEC958 ; 
#define  MIXER_LINEIN_C_S 129 
#define  MIXER_MIC_C_S 128 
 scalar_t__ SNDRV_CTL_ELEM_IFACE_PCM ; 
 struct snd_kcontrol** kctls ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,TYPE_2__*) ; 

__attribute__((used)) static int
ct_mixer_kcontrol_new(struct ct_mixer *mixer, struct snd_kcontrol_new *new)
{
	struct snd_kcontrol *kctl;
	int err;

	kctl = snd_ctl_new1(new, mixer->atc);
	if (!kctl)
		return -ENOMEM;

	if (SNDRV_CTL_ELEM_IFACE_PCM == kctl->id.iface)
		kctl->id.device = IEC958;

	err = snd_ctl_add(mixer->atc->card, kctl);
	if (err)
		return err;

	switch (new->private_value) {
	case MIXER_LINEIN_C_S:
		kctls[0] = kctl; break;
	case MIXER_MIC_C_S:
		kctls[1] = kctl; break;
	default:
		break;
	}

	return 0;
}