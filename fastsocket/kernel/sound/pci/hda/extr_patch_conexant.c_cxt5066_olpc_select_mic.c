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
struct hda_verb {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {scalar_t__ ext_mic_present; scalar_t__ dc_enable; int /*<<< orphan*/  recording; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  CXT5066_OLPC_EXT_MIC_BIAS ; 
 int /*<<< orphan*/  PIN_IN ; 
 int /*<<< orphan*/  PIN_VREF80 ; 
 int /*<<< orphan*/  cxt5066_set_olpc_dc_bias (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,struct hda_verb const*) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxt5066_olpc_select_mic(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	if (!spec->recording)
		return;

	if (spec->dc_enable) {
		/* in DC mode we ignore presence detection and just use the jack
		 * through our special DC port */
		const struct hda_verb enable_dc_mode[] = {
			/* disble internal mic, port C */
			{0x1b, AC_VERB_SET_PIN_WIDGET_CONTROL, 0},

			/* enable DC capture, port F */
			{0x1e, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_IN},
			{},
		};

		snd_hda_sequence_write(codec, enable_dc_mode);
		/* port B input disabled (and bias set) through the following call */
		cxt5066_set_olpc_dc_bias(codec);
		return;
	}

	/* disable DC (port F) */
	snd_hda_set_pin_ctl(codec, 0x1e, 0);

	/* external mic, port B */
	snd_hda_set_pin_ctl(codec, 0x1a,
		spec->ext_mic_present ? CXT5066_OLPC_EXT_MIC_BIAS : 0);

	/* internal mic, port C */
	snd_hda_set_pin_ctl(codec, 0x1b,
		spec->ext_mic_present ? 0 : PIN_VREF80);
}