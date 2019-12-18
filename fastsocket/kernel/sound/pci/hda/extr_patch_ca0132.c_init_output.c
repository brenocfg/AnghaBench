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
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int AC_WCAP_OUT_AMP ; 
 int /*<<< orphan*/  AMP_OUT_UNMUTE ; 
 int /*<<< orphan*/  AMP_OUT_ZERO ; 
 int /*<<< orphan*/  PIN_HP ; 
 int get_wcaps (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_output(struct hda_codec *codec, hda_nid_t pin, hda_nid_t dac)
{
	if (pin) {
		snd_hda_set_pin_ctl(codec, pin, PIN_HP);
		if (get_wcaps(codec, pin) & AC_WCAP_OUT_AMP)
			snd_hda_codec_write(codec, pin, 0,
					    AC_VERB_SET_AMP_GAIN_MUTE,
					    AMP_OUT_UNMUTE);
	}
	if (dac && (get_wcaps(codec, dac) & AC_WCAP_OUT_AMP))
		snd_hda_codec_write(codec, dac, 0,
				    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_ZERO);
}