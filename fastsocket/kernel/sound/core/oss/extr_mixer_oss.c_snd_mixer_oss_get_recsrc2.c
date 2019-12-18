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
struct snd_mixer_oss_slot {scalar_t__ private_data; } ;
struct snd_mixer_oss_file {struct snd_mixer_oss* mixer; struct snd_card* card; } ;
struct snd_mixer_oss {int mask_recsrc; struct snd_mixer_oss_slot* slots; } ;
struct snd_kcontrol {int (* info ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;int (* get ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;} ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ctl_elem_info {TYPE_2__ value; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;
struct slot {scalar_t__ signature; int present; scalar_t__ capture_item; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_MIXER_OSS_PRESENT_CAPTURE ; 
 scalar_t__ SNDRV_MIXER_OSS_SIGNATURE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_value*) ; 
 struct snd_ctl_elem_value* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_mixer_oss_test_id (struct snd_mixer_oss*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int stub2 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mixer_oss_get_recsrc2(struct snd_mixer_oss_file *fmixer, unsigned int *active_index)
{
	struct snd_card *card = fmixer->card;
	struct snd_mixer_oss *mixer = fmixer->mixer;
	struct snd_kcontrol *kctl;
	struct snd_mixer_oss_slot *pslot;
	struct slot *slot;
	struct snd_ctl_elem_info *uinfo;
	struct snd_ctl_elem_value *uctl;
	int err, idx;
	
	uinfo = kzalloc(sizeof(*uinfo), GFP_KERNEL);
	uctl = kzalloc(sizeof(*uctl), GFP_KERNEL);
	if (uinfo == NULL || uctl == NULL) {
		err = -ENOMEM;
		goto __free_only;
	}
	down_read(&card->controls_rwsem);
	kctl = snd_mixer_oss_test_id(mixer, "Capture Source", 0);
	if (! kctl) {
		err = -ENOENT;
		goto __unlock;
	}
	if ((err = kctl->info(kctl, uinfo)) < 0)
		goto __unlock;
	if ((err = kctl->get(kctl, uctl)) < 0)
		goto __unlock;
	for (idx = 0; idx < 32; idx++) {
		if (!(mixer->mask_recsrc & (1 << idx)))
			continue;
		pslot = &mixer->slots[idx];
		slot = (struct slot *)pslot->private_data;
		if (slot->signature != SNDRV_MIXER_OSS_SIGNATURE)
			continue;
		if (!(slot->present & SNDRV_MIXER_OSS_PRESENT_CAPTURE))
			continue;
		if (slot->capture_item == uctl->value.enumerated.item[0]) {
			*active_index = idx;
			break;
		}
	}
	err = 0;
      __unlock:
     	up_read(&card->controls_rwsem);
      __free_only:
      	kfree(uctl);
      	kfree(uinfo);
      	return err;
}