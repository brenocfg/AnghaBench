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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  hp_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxt5051_update_speaker (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void cxt5051_hp_automute(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;

	spec->hp_present = snd_hda_jack_detect(codec, 0x16);
	cxt5051_update_speaker(codec);
}