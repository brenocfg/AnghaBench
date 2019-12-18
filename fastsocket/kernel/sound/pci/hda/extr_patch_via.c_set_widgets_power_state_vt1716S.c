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
struct TYPE_2__ {scalar_t__ indep_hp_enabled; } ;
struct via_spec {TYPE_1__ gen; scalar_t__ dmic_enabled; } ;
struct hda_codec {struct via_spec* spec; } ;

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 int /*<<< orphan*/  set_pin_power_state (struct hda_codec*,int,unsigned int*) ; 
 scalar_t__ smart51_enabled (struct hda_codec*) ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 
 int /*<<< orphan*/  update_power_state (struct hda_codec*,int,unsigned int) ; 

__attribute__((used)) static void set_widgets_power_state_vt1716S(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	int imux_is_smixer;
	unsigned int parm;
	unsigned int mono_out, present;
	/* SW0 (17h) = stereo mixer */
	imux_is_smixer =
	(snd_hda_codec_read(codec, 0x17, 0,
			    AC_VERB_GET_CONNECT_SEL, 0x00) ==  5);
	/* inputs */
	/* PW 1/2/5 (1ah/1bh/1eh) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x1a, &parm);
	set_pin_power_state(codec, 0x1b, &parm);
	set_pin_power_state(codec, 0x1e, &parm);
	if (imux_is_smixer)
		parm = AC_PWRST_D0;
	/* SW0 (17h), AIW0(13h) */
	update_power_state(codec, 0x17, parm);
	update_power_state(codec, 0x13, parm);

	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x1e, &parm);
	/* PW11 (22h) */
	if (spec->dmic_enabled)
		set_pin_power_state(codec, 0x22, &parm);
	else
		update_power_state(codec, 0x22, AC_PWRST_D3);

	/* SW2(26h), AIW1(14h) */
	update_power_state(codec, 0x26, parm);
	update_power_state(codec, 0x14, parm);

	/* outputs */
	/* PW0 (19h), SW1 (18h), AOW1 (11h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x19, &parm);
	/* Smart 5.1 PW2(1bh) */
	if (smart51_enabled(codec))
		set_pin_power_state(codec, 0x1b, &parm);
	update_power_state(codec, 0x18, parm);
	update_power_state(codec, 0x11, parm);

	/* PW7 (23h), SW3 (27h), AOW3 (25h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x23, &parm);
	/* Smart 5.1 PW1(1ah) */
	if (smart51_enabled(codec))
		set_pin_power_state(codec, 0x1a, &parm);
	update_power_state(codec, 0x27, parm);

	/* Smart 5.1 PW5(1eh) */
	if (smart51_enabled(codec))
		set_pin_power_state(codec, 0x1e, &parm);
	update_power_state(codec, 0x25, parm);

	/* Mono out */
	/* SW4(28h)->MW1(29h)-> PW12 (2ah)*/
	present = snd_hda_jack_detect(codec, 0x1c);

	if (present)
		mono_out = 0;
	else {
		present = snd_hda_jack_detect(codec, 0x1d);
		if (!spec->gen.indep_hp_enabled && present)
			mono_out = 0;
		else
			mono_out = 1;
	}
	parm = mono_out ? AC_PWRST_D0 : AC_PWRST_D3;
	update_power_state(codec, 0x28, parm);
	update_power_state(codec, 0x29, parm);
	update_power_state(codec, 0x2a, parm);

	/* PW 3/4 (1ch/1dh) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x1c, &parm);
	set_pin_power_state(codec, 0x1d, &parm);
	/* HP Independent Mode, power on AOW3 */
	if (spec->gen.indep_hp_enabled)
		update_power_state(codec, 0x25, parm);

	/* force to D0 for internal Speaker */
	/* MW0 (16h), AOW0 (10h) */
	update_power_state(codec, 0x16, imux_is_smixer ? AC_PWRST_D0 : parm);
	update_power_state(codec, 0x10, mono_out ? AC_PWRST_D0 : parm);
}