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
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc_fixup_headset_mode (struct hda_codec*,struct hda_fixup const*,int) ; 
 int alc_read_coef_idx (struct hda_codec*,int) ; 
 int /*<<< orphan*/  alc_write_coef_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl_cache (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_fixup_headset_mode_alc668(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		int val;
		alc_write_coef_idx(codec, 0xc4, 0x8000);
		val = alc_read_coef_idx(codec, 0xc2);
		alc_write_coef_idx(codec, 0xc2, val & 0xfe);
		snd_hda_set_pin_ctl_cache(codec, 0x18, 0);
	}
	alc_fixup_headset_mode(codec, fix, action);
}