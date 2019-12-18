#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_jack_tbl {int dummy; } ;
struct hda_gen_spec {int am_num_entries; TYPE_1__* am_entry; int /*<<< orphan*/  auto_mic; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int AC_PINCTL_OUT_EN ; 
 int /*<<< orphan*/  mux_select (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_codec_get_pin_target (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hda_jack_detect (struct hda_codec*,int /*<<< orphan*/ ) ; 

void snd_hda_gen_mic_autoswitch(struct hda_codec *codec, struct hda_jack_tbl *jack)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	if (!spec->auto_mic)
		return;

	for (i = spec->am_num_entries - 1; i > 0; i--) {
		hda_nid_t pin = spec->am_entry[i].pin;
		/* don't detect pins retasked as outputs */
		if (snd_hda_codec_get_pin_target(codec, pin) & AC_PINCTL_OUT_EN)
			continue;
		if (snd_hda_jack_detect(codec, pin)) {
			mux_select(codec, 0, spec->am_entry[i].idx);
			return;
		}
	}
	mux_select(codec, 0, spec->am_entry[0].idx);
}