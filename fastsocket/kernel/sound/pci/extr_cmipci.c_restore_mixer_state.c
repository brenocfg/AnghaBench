#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int /*<<< orphan*/  id; int /*<<< orphan*/  (* put ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;int /*<<< orphan*/  (* get ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;TYPE_1__* vd; } ;
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct cmipci {scalar_t__* mixer_res_status; int /*<<< orphan*/  card; struct snd_kcontrol** mixer_res_ctl; scalar_t__ mixer_insensitive; } ;
struct TYPE_4__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 unsigned int CM_SAVED_MIXERS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int SNDRV_CTL_EVENT_MASK_INFO ; 
 int SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_value*) ; 
 struct snd_ctl_elem_value* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_value*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  stub2 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static void restore_mixer_state(struct cmipci *cm)
{
	if (cm->mixer_insensitive) {
		struct snd_ctl_elem_value *val;
		unsigned int i;

		val = kmalloc(sizeof(*val), GFP_KERNEL);
		if (!val)
			return;
		cm->mixer_insensitive = 0; /* at first clear this;
					      otherwise the changes will be ignored */
		for (i = 0; i < CM_SAVED_MIXERS; i++) {
			struct snd_kcontrol *ctl = cm->mixer_res_ctl[i];
			if (ctl) {
				int event;

				memset(val, 0, sizeof(*val));
				ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				ctl->get(ctl, val);
				event = SNDRV_CTL_EVENT_MASK_INFO;
				if (val->value.integer.value[0] != cm->mixer_res_status[i]) {
					val->value.integer.value[0] = cm->mixer_res_status[i];
					ctl->put(ctl, val);
					event |= SNDRV_CTL_EVENT_MASK_VALUE;
				}
				snd_ctl_notify(cm->card, event, &ctl->id);
			}
		}
		kfree(val);
	}
}