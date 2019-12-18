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
struct snd_ctl_elem_id {int /*<<< orphan*/  numid; int /*<<< orphan*/  index; } ;
struct snd_kcontrol {unsigned int count; struct snd_ctl_elem_id id; int /*<<< orphan*/  list; } ;
struct snd_card {unsigned int controls_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_REMOVE ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ctl_free_one (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 

int snd_ctl_remove(struct snd_card *card, struct snd_kcontrol *kcontrol)
{
	struct snd_ctl_elem_id id;
	unsigned int idx;

	if (snd_BUG_ON(!card || !kcontrol))
		return -EINVAL;
	list_del(&kcontrol->list);
	card->controls_count -= kcontrol->count;
	id = kcontrol->id;
	for (idx = 0; idx < kcontrol->count; idx++, id.index++, id.numid++)
		snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_REMOVE, &id);
	snd_ctl_free_one(kcontrol);
	return 0;
}