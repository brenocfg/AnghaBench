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
struct hda_jack_tbl {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int /*<<< orphan*/  current_headset_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_HEADSET_MODE_UNKNOWN ; 
 int /*<<< orphan*/  snd_hda_gen_hp_automute (struct hda_codec*,struct hda_jack_tbl*) ; 

__attribute__((used)) static void alc_update_headset_jack_cb(struct hda_codec *codec, struct hda_jack_tbl *jack)
{
	struct alc_spec *spec = codec->spec;
	spec->current_headset_type = ALC_HEADSET_MODE_UNKNOWN;
	snd_hda_gen_hp_automute(codec, jack);
}