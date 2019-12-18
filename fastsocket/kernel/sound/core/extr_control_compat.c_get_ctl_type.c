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
struct snd_kcontrol {int (* info ) (struct snd_kcontrol*,struct snd_ctl_elem_info*) ;} ;
struct snd_ctl_elem_id {int dummy; } ;
struct snd_ctl_elem_info {int type; int count; struct snd_ctl_elem_id id; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_info*) ; 
 struct snd_ctl_elem_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 int stub1 (struct snd_kcontrol*,struct snd_ctl_elem_info*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_ctl_type(struct snd_card *card, struct snd_ctl_elem_id *id,
			int *countp)
{
	struct snd_kcontrol *kctl;
	struct snd_ctl_elem_info *info;
	int err;

	down_read(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, id);
	if (! kctl) {
		up_read(&card->controls_rwsem);
		return -ENXIO;
	}
	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) {
		up_read(&card->controls_rwsem);
		return -ENOMEM;
	}
	info->id = *id;
	err = kctl->info(kctl, info);
	up_read(&card->controls_rwsem);
	if (err >= 0) {
		err = info->type;
		*countp = info->count;
	}
	kfree(info);
	return err;
}