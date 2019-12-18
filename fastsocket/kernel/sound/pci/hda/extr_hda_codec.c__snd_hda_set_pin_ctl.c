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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  snd_hda_codec_set_pin_target (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_hda_codec_update_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int snd_hda_correct_pin_ctl (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

int _snd_hda_set_pin_ctl(struct hda_codec *codec, hda_nid_t pin,
			 unsigned int val, bool cached)
{
	val = snd_hda_correct_pin_ctl(codec, pin, val);
	snd_hda_codec_set_pin_target(codec, pin, val);
	if (cached)
		return snd_hda_codec_update_cache(codec, pin, 0,
				AC_VERB_SET_PIN_WIDGET_CONTROL, val);
	else
		return snd_hda_codec_write(codec, pin, 0,
					   AC_VERB_SET_PIN_WIDGET_CONTROL, val);
}