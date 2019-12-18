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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 unsigned int AC_GPIO_IO_COUNT ; 
 int /*<<< orphan*/  AC_PAR_GPIO_CAP ; 
#define  HDA_FIXUP_ACT_PRE_PROBE 129 
#define  HDA_FIXUP_ACT_PROBE 128 
 int /*<<< orphan*/  snd_hda_codec_set_pincfg (struct hda_codec*,int,int) ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac_add_hp_bass_switch (struct hda_codec*) ; 

__attribute__((used)) static void stac92hd71bxx_fixup_hp_dv5(struct hda_codec *codec,
				       const struct hda_fixup *fix, int action)
{
	unsigned int cap;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_codec_set_pincfg(codec, 0x0d, 0x90170010);
		break;

	case HDA_FIXUP_ACT_PROBE:
		/* enable bass on HP dv7 */
		cap = snd_hda_param_read(codec, 0x1, AC_PAR_GPIO_CAP);
		cap &= AC_GPIO_IO_COUNT;
		if (cap >= 6)
			stac_add_hp_bass_switch(codec);
		break;
	}
}