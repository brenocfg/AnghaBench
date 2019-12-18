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
struct via_spec {unsigned int no_pin_power_ctl; } ;
struct hda_codec {struct via_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_DEFCFG_MISC ; 
 unsigned int AC_DEFCFG_MISC_NO_PRESENCE ; 
 unsigned int AC_DEFCFG_MISC_SHIFT ; 
 scalar_t__ AC_JACK_PORT_NONE ; 
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 scalar_t__ get_defcfg_connect (unsigned int) ; 
 scalar_t__ is_smart51_pins (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ smart51_enabled (struct hda_codec*) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_power_state (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_pin_power_state(struct hda_codec *codec, hda_nid_t nid,
				unsigned int *affected_parm)
{
	unsigned parm;
	unsigned def_conf = snd_hda_codec_get_pincfg(codec, nid);
	unsigned no_presence = (def_conf & AC_DEFCFG_MISC)
		>> AC_DEFCFG_MISC_SHIFT
		& AC_DEFCFG_MISC_NO_PRESENCE; /* do not support pin sense */
	struct via_spec *spec = codec->spec;
	unsigned present = 0;

	no_presence |= spec->no_pin_power_ctl;
	if (!no_presence)
		present = snd_hda_jack_detect(codec, nid);
	if ((smart51_enabled(codec) && is_smart51_pins(codec, nid))
	    || ((no_presence || present)
		&& get_defcfg_connect(def_conf) != AC_JACK_PORT_NONE)) {
		*affected_parm = AC_PWRST_D0; /* if it's connected */
		parm = AC_PWRST_D0;
	} else
		parm = AC_PWRST_D3;

	update_power_state(codec, nid, parm);
}