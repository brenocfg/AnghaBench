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
 int AC_AMP_GET_LEFT ; 
 int AC_AMP_GET_OUTPUT ; 
 int AC_AMP_GET_RIGHT ; 
 int AC_AMP_SET_OUTPUT ; 
 int AC_AMP_SET_RIGHT ; 
 int AC_PWRST_ACTUAL ; 
 int AC_PWRST_ACTUAL_SHIFT ; 
 int AC_PWRST_D0 ; 
 int /*<<< orphan*/  AC_VERB_GET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_GET_POWER_STATE ; 
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_check_power_state (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_printd (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void haswell_verify_pin_D0(struct hda_codec *codec,
		hda_nid_t cvt_nid, hda_nid_t nid)
{
	int pwr, lamp, ramp;

	/* For Haswell, the converter 1/2 may keep in D3 state after bootup,
	 * thus pins could only choose converter 0 for use. Make sure the
	 * converters are in correct power state */
	if (!snd_hda_check_power_state(codec, cvt_nid, AC_PWRST_D0))
		snd_hda_codec_write(codec, cvt_nid, 0, AC_VERB_SET_POWER_STATE, AC_PWRST_D0);

	if (!snd_hda_check_power_state(codec, nid, AC_PWRST_D0)) {
		snd_hda_codec_write(codec, nid, 0, AC_VERB_SET_POWER_STATE,
				    AC_PWRST_D0);
		msleep(40);
		pwr = snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_POWER_STATE, 0);
		pwr = (pwr & AC_PWRST_ACTUAL) >> AC_PWRST_ACTUAL_SHIFT;
		snd_printd("Haswell HDMI audio: Power for pin 0x%x is now D%d\n", nid, pwr);
	}

	lamp = snd_hda_codec_read(codec, nid, 0,
				  AC_VERB_GET_AMP_GAIN_MUTE,
				  AC_AMP_GET_LEFT | AC_AMP_GET_OUTPUT);
	ramp = snd_hda_codec_read(codec, nid, 0,
				  AC_VERB_GET_AMP_GAIN_MUTE,
				  AC_AMP_GET_RIGHT | AC_AMP_GET_OUTPUT);
	if (lamp != ramp) {
		snd_hda_codec_write(codec, nid, 0, AC_VERB_SET_AMP_GAIN_MUTE,
				    AC_AMP_SET_RIGHT | AC_AMP_SET_OUTPUT | lamp);

		lamp = snd_hda_codec_read(codec, nid, 0,
				  AC_VERB_GET_AMP_GAIN_MUTE,
				  AC_AMP_GET_LEFT | AC_AMP_GET_OUTPUT);
		ramp = snd_hda_codec_read(codec, nid, 0,
				  AC_VERB_GET_AMP_GAIN_MUTE,
				  AC_AMP_GET_RIGHT | AC_AMP_GET_OUTPUT);
		snd_printd("Haswell HDMI audio: Mute after set on pin 0x%x: [0x%x 0x%x]\n", nid, lamp, ramp);
	}
}