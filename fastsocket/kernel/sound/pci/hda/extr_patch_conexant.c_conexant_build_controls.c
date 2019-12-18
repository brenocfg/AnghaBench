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
struct hda_codec {struct conexant_spec* spec; } ;
struct TYPE_2__ {int share_spdif; scalar_t__ dig_out_nid; } ;
struct conexant_spec {unsigned int num_mixers; scalar_t__ input_mux; scalar_t__ vmaster_nid; scalar_t__ dig_in_nid; TYPE_1__ multiout; int /*<<< orphan*/ * mixers; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int add_beep_ctls (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt_capture_mixers ; 
 int /*<<< orphan*/  slave_pfxs ; 
 int snd_hda_add_new_ctls (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_add_vmaster (struct hda_codec*,char*,unsigned int*,int /*<<< orphan*/ ,char*) ; 
 int snd_hda_create_spdif_in_ctls (struct hda_codec*,scalar_t__) ; 
 int snd_hda_create_spdif_out_ctls (struct hda_codec*,scalar_t__,scalar_t__) ; 
 int snd_hda_create_spdif_share_sw (struct hda_codec*,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_hda_find_mixer_ctl (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  snd_hda_set_vmaster_tlv (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int conexant_build_controls(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int i;
	int err;

	for (i = 0; i < spec->num_mixers; i++) {
		err = snd_hda_add_new_ctls(codec, spec->mixers[i]);
		if (err < 0)
			return err;
	}
	if (spec->multiout.dig_out_nid) {
		err = snd_hda_create_spdif_out_ctls(codec,
						    spec->multiout.dig_out_nid,
						    spec->multiout.dig_out_nid);
		if (err < 0)
			return err;
		err = snd_hda_create_spdif_share_sw(codec,
						    &spec->multiout);
		if (err < 0)
			return err;
		spec->multiout.share_spdif = 1;
	} 
	if (spec->dig_in_nid) {
		err = snd_hda_create_spdif_in_ctls(codec,spec->dig_in_nid);
		if (err < 0)
			return err;
	}

	/* if we have no master control, let's create it */
	if (spec->vmaster_nid &&
	    !snd_hda_find_mixer_ctl(codec, "Master Playback Volume")) {
		unsigned int vmaster_tlv[4];
		snd_hda_set_vmaster_tlv(codec, spec->vmaster_nid,
					HDA_OUTPUT, vmaster_tlv);
		err = snd_hda_add_vmaster(codec, "Master Playback Volume",
					  vmaster_tlv, slave_pfxs,
					  "Playback Volume");
		if (err < 0)
			return err;
	}
	if (spec->vmaster_nid &&
	    !snd_hda_find_mixer_ctl(codec, "Master Playback Switch")) {
		err = snd_hda_add_vmaster(codec, "Master Playback Switch",
					  NULL, slave_pfxs,
					  "Playback Switch");
		if (err < 0)
			return err;
	}

	if (spec->input_mux) {
		err = snd_hda_add_new_ctls(codec, cxt_capture_mixers);
		if (err < 0)
			return err;
	}

	err = add_beep_ctls(codec);
	if (err < 0)
		return err;

	return 0;
}