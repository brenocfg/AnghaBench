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
struct snd_kcontrol_volatile {int access; } ;
struct snd_kcontrol {int (* get ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;struct snd_kcontrol_volatile* vd; } ;
struct snd_ctl_elem_value {int /*<<< orphan*/  id; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int SNDRV_CTL_ELEM_ACCESS_READ ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ctl_build_ioff (int /*<<< orphan*/ *,struct snd_kcontrol*,unsigned int) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,int /*<<< orphan*/ *) ; 
 unsigned int snd_ctl_get_ioff (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 int stub1 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ctl_elem_read(struct snd_card *card,
			     struct snd_ctl_elem_value *control)
{
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_volatile *vd;
	unsigned int index_offset;
	int result;

	down_read(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, &control->id);
	if (kctl == NULL) {
		result = -ENOENT;
	} else {
		index_offset = snd_ctl_get_ioff(kctl, &control->id);
		vd = &kctl->vd[index_offset];
		if ((vd->access & SNDRV_CTL_ELEM_ACCESS_READ) &&
		    kctl->get != NULL) {
			snd_ctl_build_ioff(&control->id, kctl, index_offset);
			result = kctl->get(kctl, control);
		} else
			result = -EPERM;
	}
	up_read(&card->controls_rwsem);
	return result;
}