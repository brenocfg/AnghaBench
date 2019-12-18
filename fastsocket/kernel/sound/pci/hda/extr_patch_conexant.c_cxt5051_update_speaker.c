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
struct conexant_spec {scalar_t__ ideapad; scalar_t__ cur_eapd; scalar_t__ hp_present; } ;

/* Variables and functions */
 unsigned int PIN_HP ; 
 unsigned int PIN_OUT ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl (struct hda_codec*,int,unsigned int) ; 

__attribute__((used)) static void cxt5051_update_speaker(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int pinctl;
	/* headphone pin */
	pinctl = (spec->hp_present && spec->cur_eapd) ? PIN_HP : 0;
	snd_hda_set_pin_ctl(codec, 0x16, pinctl);
	/* speaker pin */
	pinctl = (!spec->hp_present && spec->cur_eapd) ? PIN_OUT : 0;
	snd_hda_set_pin_ctl(codec, 0x1a, pinctl);
	/* on ideapad there is an additional speaker (subwoofer) to mute */
	if (spec->ideapad)
		snd_hda_set_pin_ctl(codec, 0x1b, pinctl);
}