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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;
struct pcxhr_mgr {scalar_t__ is_hr_stereo; scalar_t__ capture_chips; scalar_t__ board_has_aes1; } ;

/* Variables and functions */
 int HR22_CLOCK_TYPE_MAX ; 
 int PCXHR_CLOCK_TYPE_MAX ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 struct pcxhr_mgr* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int pcxhr_clock_type_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	static const char *textsPCXHR[7] = {
		"Internal", "WordClock", "AES Sync",
		"AES 1", "AES 2", "AES 3", "AES 4"
	};
	static const char *textsHR22[3] = {
		"Internal", "AES Sync", "AES 1"
	};
	const char **texts;
	struct pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	int clock_items = 2;	/* at least Internal and AES Sync clock */
	if (mgr->board_has_aes1) {
		clock_items += mgr->capture_chips;	/* add AES x */
		if (!mgr->is_hr_stereo)
			clock_items += 1;		/* add word clock */
	}
	if (mgr->is_hr_stereo) {
		texts = textsHR22;
		snd_BUG_ON(clock_items > (HR22_CLOCK_TYPE_MAX+1));
	} else {
		texts = textsPCXHR;
		snd_BUG_ON(clock_items > (PCXHR_CLOCK_TYPE_MAX+1));
	}
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = clock_items;
	if (uinfo->value.enumerated.item >= clock_items)
		uinfo->value.enumerated.item = clock_items-1;
	strcpy(uinfo->value.enumerated.name,
		texts[uinfo->value.enumerated.item]);
	return 0;
}