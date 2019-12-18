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
struct hdmi_spec {int dummy; } ;
struct hda_jack_tbl {int nid; int jack_dirty; } ;
struct hda_codec {int /*<<< orphan*/  addr; struct hdmi_spec* spec; } ;

/* Variables and functions */
 unsigned int AC_UNSOL_RES_ELDV ; 
 unsigned int AC_UNSOL_RES_PD ; 
 unsigned int AC_UNSOL_RES_TAG_SHIFT ; 
 int /*<<< orphan*/  SND_PR_VERBOSE ; 
 int /*<<< orphan*/  _snd_printd (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  get_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  hdmi_present_sense (int /*<<< orphan*/ ,int) ; 
 int pin_nid_to_pin_index (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  snd_hda_jack_report_sync (struct hda_codec*) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get_from_tag (struct hda_codec*,int) ; 

__attribute__((used)) static void hdmi_intrinsic_event(struct hda_codec *codec, unsigned int res)
{
	struct hdmi_spec *spec = codec->spec;
	int tag = res >> AC_UNSOL_RES_TAG_SHIFT;
	int pin_nid;
	int pin_idx;
	struct hda_jack_tbl *jack;

	jack = snd_hda_jack_tbl_get_from_tag(codec, tag);
	if (!jack)
		return;
	pin_nid = jack->nid;
	jack->jack_dirty = 1;

	_snd_printd(SND_PR_VERBOSE,
		"HDMI hot plug event: Codec=%d Pin=%d Presence_Detect=%d ELD_Valid=%d\n",
		codec->addr, pin_nid,
		!!(res & AC_UNSOL_RES_PD), !!(res & AC_UNSOL_RES_ELDV));

	pin_idx = pin_nid_to_pin_index(spec, pin_nid);
	if (pin_idx < 0)
		return;

	hdmi_present_sense(get_pin(spec, pin_idx), 1);
	snd_hda_jack_report_sync(codec);
}