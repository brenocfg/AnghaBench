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
struct snd_mixer_oss_slot {int stereo; int /*<<< orphan*/  private_free; struct slot* private_data; int /*<<< orphan*/  put_recsrc; int /*<<< orphan*/  get_recsrc; int /*<<< orphan*/  put_volume; scalar_t__ get_volume; } ;
struct snd_mixer_oss_assign_table {size_t oss_id; scalar_t__ index; char* name; } ;
struct snd_mixer_oss {int mask_recsrc; struct snd_mixer_oss_slot* slots; TYPE_3__* card; } ;
struct snd_kcontrol {scalar_t__ (* info ) (struct snd_kcontrol*,struct snd_ctl_elem_info*) ;} ;
struct TYPE_4__ {char* name; scalar_t__ items; scalar_t__ item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {TYPE_2__ value; } ;
struct slot {int capture_item; int present; int allocated; int channels; struct snd_mixer_oss_assign_table* assigned; int /*<<< orphan*/  signature; struct slot* numid; } ;
typedef  int /*<<< orphan*/  slot ;
struct TYPE_6__ {int /*<<< orphan*/  controls_rwsem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_MIXER_OSS_PRESENT_CAPTURE ; 
 int SNDRV_MIXER_OSS_PRESENT_CROUTE ; 
 int SNDRV_MIXER_OSS_PRESENT_CSWITCH ; 
 int /*<<< orphan*/  SNDRV_MIXER_OSS_SIGNATURE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_info*) ; 
 struct slot* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_ctl_elem_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct slot*,int,int) ; 
 int /*<<< orphan*/  mixer_slot_clear (struct snd_mixer_oss_slot*) ; 
 scalar_t__ snd_mixer_oss_build_test_all (struct snd_mixer_oss*,struct snd_mixer_oss_assign_table*,struct slot*) ; 
 int /*<<< orphan*/  snd_mixer_oss_get_recsrc1_route ; 
 int /*<<< orphan*/  snd_mixer_oss_get_recsrc1_sw ; 
 scalar_t__ snd_mixer_oss_get_volume1 ; 
 int /*<<< orphan*/  snd_mixer_oss_put_recsrc1_route ; 
 int /*<<< orphan*/  snd_mixer_oss_put_recsrc1_sw ; 
 int /*<<< orphan*/  snd_mixer_oss_put_volume1 ; 
 int /*<<< orphan*/  snd_mixer_oss_slot_free ; 
 struct snd_kcontrol* snd_mixer_oss_test_id (struct snd_mixer_oss*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ stub1 (struct snd_kcontrol*,struct snd_ctl_elem_info*) ; 
 scalar_t__ stub2 (struct snd_kcontrol*,struct snd_ctl_elem_info*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mixer_oss_build_input(struct snd_mixer_oss *mixer, struct snd_mixer_oss_assign_table *ptr, int ptr_allocated, int replace_old)
{
	struct slot slot;
	struct slot *pslot;
	struct snd_kcontrol *kctl;
	struct snd_mixer_oss_slot *rslot;
	char str[64];	
	
	/* check if already assigned */
	if (mixer->slots[ptr->oss_id].get_volume && ! replace_old)
		return 0;

	memset(&slot, 0, sizeof(slot));
	memset(slot.numid, 0xff, sizeof(slot.numid)); /* ID_UNKNOWN */
	if (snd_mixer_oss_build_test_all(mixer, ptr, &slot))
		return 0;
	down_read(&mixer->card->controls_rwsem);
	if (ptr->index == 0 && (kctl = snd_mixer_oss_test_id(mixer, "Capture Source", 0)) != NULL) {
		struct snd_ctl_elem_info *uinfo;

		uinfo = kzalloc(sizeof(*uinfo), GFP_KERNEL);
		if (! uinfo) {
			up_read(&mixer->card->controls_rwsem);
			return -ENOMEM;
		}
			
		if (kctl->info(kctl, uinfo)) {
			up_read(&mixer->card->controls_rwsem);
			return 0;
		}
		strcpy(str, ptr->name);
		if (!strcmp(str, "Master"))
			strcpy(str, "Mix");
		if (!strcmp(str, "Master Mono"))
			strcpy(str, "Mix Mono");
		slot.capture_item = 0;
		if (!strcmp(uinfo->value.enumerated.name, str)) {
			slot.present |= SNDRV_MIXER_OSS_PRESENT_CAPTURE;
		} else {
			for (slot.capture_item = 1; slot.capture_item < uinfo->value.enumerated.items; slot.capture_item++) {
				uinfo->value.enumerated.item = slot.capture_item;
				if (kctl->info(kctl, uinfo)) {
					up_read(&mixer->card->controls_rwsem);
					return 0;
				}
				if (!strcmp(uinfo->value.enumerated.name, str)) {
					slot.present |= SNDRV_MIXER_OSS_PRESENT_CAPTURE;
					break;
				}
			}
		}
		kfree(uinfo);
	}
	up_read(&mixer->card->controls_rwsem);
	if (slot.present != 0) {
		pslot = kmalloc(sizeof(slot), GFP_KERNEL);
		if (! pslot)
			return -ENOMEM;
		*pslot = slot;
		pslot->signature = SNDRV_MIXER_OSS_SIGNATURE;
		pslot->assigned = ptr;
		pslot->allocated = ptr_allocated;
		rslot = &mixer->slots[ptr->oss_id];
		mixer_slot_clear(rslot);
		rslot->stereo = slot.channels > 1 ? 1 : 0;
		rslot->get_volume = snd_mixer_oss_get_volume1;
		rslot->put_volume = snd_mixer_oss_put_volume1;
		/* note: ES18xx have both Capture Source and XX Capture Volume !!! */
		if (slot.present & SNDRV_MIXER_OSS_PRESENT_CSWITCH) {
			rslot->get_recsrc = snd_mixer_oss_get_recsrc1_sw;
			rslot->put_recsrc = snd_mixer_oss_put_recsrc1_sw;
		} else if (slot.present & SNDRV_MIXER_OSS_PRESENT_CROUTE) {
			rslot->get_recsrc = snd_mixer_oss_get_recsrc1_route;
			rslot->put_recsrc = snd_mixer_oss_put_recsrc1_route;
		} else if (slot.present & SNDRV_MIXER_OSS_PRESENT_CAPTURE) {
			mixer->mask_recsrc |= 1 << ptr->oss_id;
		}
		rslot->private_data = pslot;
		rslot->private_free = snd_mixer_oss_slot_free;
		return 1;
	}
	return 0;
}