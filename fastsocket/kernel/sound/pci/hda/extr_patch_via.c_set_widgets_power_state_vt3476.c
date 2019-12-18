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
struct via_spec {scalar_t__ codec_type; TYPE_1__ gen; } ;
struct hda_codec {struct via_spec* spec; } ;

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 scalar_t__ VT1705CF ; 
 int /*<<< orphan*/  set_pin_power_state (struct hda_codec*,int,unsigned int*) ; 
 scalar_t__ smart51_enabled (struct hda_codec*) ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_conv_power_state (struct hda_codec*,int,unsigned int,int) ; 
 int /*<<< orphan*/  update_power_state (struct hda_codec*,int,unsigned int) ; 

__attribute__((used)) static void set_widgets_power_state_vt3476(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	int imux_is_smixer;
	unsigned int parm, parm2;
	/* MUX10 (1eh) = stereo mixer */
	imux_is_smixer =
	snd_hda_codec_read(codec, 0x1e, 0, AC_VERB_GET_CONNECT_SEL, 0x00) == 4;
	/* inputs */
	/* PW 5/6/7 (29h/2ah/2bh) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x29, &parm);
	set_pin_power_state(codec, 0x2a, &parm);
	set_pin_power_state(codec, 0x2b, &parm);
	if (imux_is_smixer)
		parm = AC_PWRST_D0;
	/* MUX10/11 (1eh/1fh), AIW 0/1 (10h/11h) */
	update_power_state(codec, 0x1e, parm);
	update_power_state(codec, 0x1f, parm);
	update_power_state(codec, 0x10, parm);
	update_power_state(codec, 0x11, parm);

	/* outputs */
	/* PW3 (27h), MW3(37h), AOW3 (bh) */
	if (spec->codec_type == VT1705CF) {
		parm = AC_PWRST_D3;
		update_power_state(codec, 0x27, parm);
		update_power_state(codec, 0x37, parm);
	}	else {
		parm = AC_PWRST_D3;
		set_pin_power_state(codec, 0x27, &parm);
		update_power_state(codec, 0x37, parm);
	}

	/* PW2 (26h), MW2(36h), AOW2 (ah) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x26, &parm);
	update_power_state(codec, 0x36, parm);
	if (smart51_enabled(codec)) {
		/* PW7(2bh), MW7(3bh), MUX7(1Bh) */
		set_pin_power_state(codec, 0x2b, &parm);
		update_power_state(codec, 0x3b, parm);
		update_power_state(codec, 0x1b, parm);
	}
	update_conv_power_state(codec, 0xa, parm, 2);

	/* PW1 (25h), MW1(35h), AOW1 (9h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x25, &parm);
	update_power_state(codec, 0x35, parm);
	if (smart51_enabled(codec)) {
		/* PW6(2ah), MW6(3ah), MUX6(1ah) */
		set_pin_power_state(codec, 0x2a, &parm);
		update_power_state(codec, 0x3a, parm);
		update_power_state(codec, 0x1a, parm);
	}
	update_conv_power_state(codec, 0x9, parm, 1);

	/* PW4 (28h), MW4 (38h), MUX4(18h), AOW3(bh)/AOW0(8h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x28, &parm);
	update_power_state(codec, 0x38, parm);
	update_power_state(codec, 0x18, parm);
	if (spec->gen.indep_hp_enabled)
		update_conv_power_state(codec, 0xb, parm, 3);
	parm2 = parm; /* for pin 0x0b */

	/* PW0 (24h), MW0(34h), MW9(3fh), AOW0 (8h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x24, &parm);
	update_power_state(codec, 0x34, parm);
	if (!spec->gen.indep_hp_enabled && parm2 != AC_PWRST_D3)
		parm = parm2;
	update_conv_power_state(codec, 0x8, parm, 0);
	/* MW9 (21h), Mw2 (1ah), AOW0 (8h) */
	update_power_state(codec, 0x3f, imux_is_smixer ? AC_PWRST_D0 : parm);
}