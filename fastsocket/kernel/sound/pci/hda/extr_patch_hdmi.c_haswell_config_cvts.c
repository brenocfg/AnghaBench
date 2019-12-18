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
struct hdmi_spec_per_pin {int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {int num_pins; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 int /*<<< orphan*/  AC_VERB_SET_CONNECT_SEL ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int hdmi_choose_cvt (struct hda_codec*,int,int /*<<< orphan*/ *,int*) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int,int) ; 

__attribute__((used)) static void haswell_config_cvts(struct hda_codec *codec,
			int pin_id, int mux_id)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin;
	int pin_idx, mux_idx;
	int curr;
	int err;

	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		per_pin = get_pin(spec, pin_idx);

		if (pin_idx == pin_id)
			continue;

		curr = snd_hda_codec_read(codec, per_pin->pin_nid, 0,
					  AC_VERB_GET_CONNECT_SEL, 0);

		/* Choose another unused converter */
		if (curr == mux_id) {
			err = hdmi_choose_cvt(codec, pin_idx, NULL, &mux_idx);
			if (err < 0)
				return;
			snd_printdd("HDMI: choose converter %d for pin %d\n", mux_idx, pin_idx);
			snd_hda_codec_write_cache(codec, per_pin->pin_nid, 0,
					    AC_VERB_SET_CONNECT_SEL,
					    mux_idx);
		}
	}
}