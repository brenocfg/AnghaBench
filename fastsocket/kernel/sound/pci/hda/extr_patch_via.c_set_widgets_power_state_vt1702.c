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

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 int /*<<< orphan*/  set_pin_power_state (struct hda_codec*,int,unsigned int*) ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_power_state (struct hda_codec*,int,unsigned int) ; 

__attribute__((used)) static void set_widgets_power_state_vt1702(struct hda_codec *codec)
{
	int imux_is_smixer =
	snd_hda_codec_read(codec, 0x13, 0, AC_VERB_GET_CONNECT_SEL, 0x00) == 3;
	unsigned int parm;
	/* inputs */
	/* PW 1/2/5 (14h/15h/18h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x14, &parm);
	set_pin_power_state(codec, 0x15, &parm);
	set_pin_power_state(codec, 0x18, &parm);
	if (imux_is_smixer)
		parm = AC_PWRST_D0; /* SW0 (13h) = stereo mixer (idx 3) */
	/* SW0 (13h), AIW 0/1/2 (12h/1fh/20h) */
	update_power_state(codec, 0x13, parm);
	update_power_state(codec, 0x12, parm);
	update_power_state(codec, 0x1f, parm);
	update_power_state(codec, 0x20, parm);

	/* outputs */
	/* PW 3/4 (16h/17h) */
	parm = AC_PWRST_D3;
	set_pin_power_state(codec, 0x17, &parm);
	set_pin_power_state(codec, 0x16, &parm);
	/* MW0 (1ah), AOW 0/1 (10h/1dh) */
	update_power_state(codec, 0x1a, imux_is_smixer ? AC_PWRST_D0 : parm);
	update_power_state(codec, 0x10, parm);
	update_power_state(codec, 0x1d, parm);
}