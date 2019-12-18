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
struct hda_codec {struct ad198x_spec* spec; } ;
struct ad198x_spec {int jack_present; scalar_t__ inv_jack_detect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad1986a_update_hp (struct hda_codec*) ; 
 int snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void ad1986a_hp_automute(struct hda_codec *codec)
{
	struct ad198x_spec *spec = codec->spec;

	spec->jack_present = snd_hda_jack_detect(codec, 0x1a);
	if (spec->inv_jack_detect)
		spec->jack_present = !spec->jack_present;
	ad1986a_update_hp(codec);
}