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
struct hda_codec {int vendor_id; struct via_spec* spec; } ;

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 scalar_t__ VT1708B_4CH ; 
 scalar_t__ VT1708S ; 
 int /*<<< orphan*/  set_pin_power_state (struct hda_codec*,int,unsigned int*) ; 
 scalar_t__ smart51_enabled (struct hda_codec*) ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_power_state (struct hda_codec*,int,unsigned int) ; 

__attribute__((used)) static void set_widgets_power_state_vt1708B(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	int imux_is_smixer;
	unsigned int parm;
	int is_8ch = 0;
	if ((spec->codec_type != VT1708B_4CH) &&
	    (codec->vendor_id != 0x11064397))
		is_8ch = 1;

	/* SW0 (17h) = stereo mixer */
	imux_is_smixer =
	(snd_hda_codec_read(codec, 0x17, 0, AC_VERB_GET_CONNECT_SEL, 0x00)
	 == ((spec->codec_type == VT1708S) ? 5 : 0));
	/* inputs */
	/* PW 1/2/5 (1ah/1bh/1eh) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x1a, &parm);
	set_pin_power_state(codec, 0x1b, &parm);
	set_pin_power_state(codec, 0x1e, &parm);
	if (imux_is_smixer)
		parm = AC_PWRST_D0;
	/* SW0 (17h), AIW 0/1 (13h/14h) */
	update_power_state(codec, 0x17, parm);
	update_power_state(codec, 0x13, parm);
	update_power_state(codec, 0x14, parm);

	/* outputs */
	/* PW0 (19h), SW1 (18h), AOW1 (11h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x19, &parm);
	if (smart51_enabled(codec))
		set_pin_power_state(codec, 0x1b, &parm);
	update_power_state(codec, 0x18, parm);
	update_power_state(codec, 0x11, parm);

	/* PW6 (22h), SW2 (26h), AOW2 (24h) */
	if (is_8ch) {
		parm = AC_PWRST_D3;
		set_pin_power_state(codec, 0x22, &parm);
		if (smart51_enabled(codec))
			set_pin_power_state(codec, 0x1a, &parm);
		update_power_state(codec, 0x26, parm);
		update_power_state(codec, 0x24, parm);
	} else if (codec->vendor_id == 0x11064397) {
		/* PW7(23h), SW2(27h), AOW2(25h) */
		parm = AC_PWRST_D3;
		set_pin_power_state(codec, 0x23, &parm);
		if (smart51_enabled(codec))
			set_pin_power_state(codec, 0x1a, &parm);
		update_power_state(codec, 0x27, parm);
		update_power_state(codec, 0x25, parm);
	}

	/* PW 3/4/7 (1ch/1dh/23h) */
	parm = AC_PWRST_D3;
	/* force to D0 for internal Speaker */
	set_pin_power_state(codec, 0x1c, &parm);
	set_pin_power_state(codec, 0x1d, &parm);
	if (is_8ch)
		set_pin_power_state(codec, 0x23, &parm);

	/* MW0 (16h), Sw3 (27h), AOW 0/3 (10h/25h) */
	update_power_state(codec, 0x16, imux_is_smixer ? AC_PWRST_D0 : parm);
	update_power_state(codec, 0x10, parm);
	if (is_8ch) {
		update_power_state(codec, 0x25, parm);
		update_power_state(codec, 0x27, parm);
	} else if (codec->vendor_id == 0x11064397 && spec->gen.indep_hp_enabled)
		update_power_state(codec, 0x25, parm);
}