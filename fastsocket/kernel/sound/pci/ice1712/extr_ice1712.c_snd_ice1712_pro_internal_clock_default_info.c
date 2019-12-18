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

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int snd_ice1712_pro_internal_clock_default_info(struct snd_kcontrol *kcontrol,
						       struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts[] = {
		"8000",		/* 0: 6 */
		"9600",		/* 1: 3 */
		"11025",	/* 2: 10 */
		"12000",	/* 3: 2 */
		"16000",	/* 4: 5 */
		"22050",	/* 5: 9 */
		"24000",	/* 6: 1 */
		"32000",	/* 7: 4 */
		"44100",	/* 8: 8 */
		"48000",	/* 9: 0 */
		"64000",	/* 10: 15 */
		"88200",	/* 11: 11 */
		"96000",	/* 12: 7 */
		/* "IEC958 Input",	13: -- */
	};
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = 13;
	if (uinfo->value.enumerated.item >= uinfo->value.enumerated.items)
		uinfo->value.enumerated.item = uinfo->value.enumerated.items - 1;
	strcpy(uinfo->value.enumerated.name, texts[uinfo->value.enumerated.item]);
	return 0;
}