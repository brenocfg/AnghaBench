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
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {scalar_t__ hp_jack_present; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int PIN_VREF80 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_gen_hp_automute (struct hda_codec*,struct hda_jack_tbl*) ; 

__attribute__((used)) static void alc269_x101_hp_automute_hook(struct hda_codec *codec,
					 struct hda_jack_tbl *jack)
{
	struct alc_spec *spec = codec->spec;
	int vref;
	msleep(200);
	snd_hda_gen_hp_automute(codec, jack);

	vref = spec->gen.hp_jack_present ? PIN_VREF80 : 0;
	msleep(100);
	snd_hda_codec_write(codec, 0x18, 0, AC_VERB_SET_PIN_WIDGET_CONTROL,
			    vref);
	msleep(500);
	snd_hda_codec_write(codec, 0x18, 0, AC_VERB_SET_PIN_WIDGET_CONTROL,
			    vref);
}