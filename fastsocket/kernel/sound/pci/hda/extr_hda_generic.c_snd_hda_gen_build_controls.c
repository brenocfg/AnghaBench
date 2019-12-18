#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hook; int /*<<< orphan*/  sw_kctl; } ;
struct TYPE_7__ {int share_spdif; scalar_t__ dig_out_nid; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; scalar_t__ used; } ;
struct hda_gen_spec {int /*<<< orphan*/  autocfg; int /*<<< orphan*/  vmaster_mute_enum; TYPE_4__ vmaster_mute; int /*<<< orphan*/  no_analog; int /*<<< orphan*/  vmaster_tlv; scalar_t__ dig_in_nid; TYPE_3__ multiout; TYPE_2__* pcm_rec; TYPE_1__ kctls; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcm_type; } ;

/* Variables and functions */
 int __snd_hda_add_vmaster (struct hda_codec*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_kctls (struct hda_gen_spec*) ; 
 int /*<<< orphan*/  slave_pfxs ; 
 int snd_hda_add_new_ctls (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_add_vmaster (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_hda_add_vmaster_hook (struct hda_codec*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int snd_hda_create_dig_out_ctls (struct hda_codec*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int snd_hda_create_spdif_in_ctls (struct hda_codec*,scalar_t__) ; 
 int snd_hda_create_spdif_share_sw (struct hda_codec*,TYPE_3__*) ; 
 int /*<<< orphan*/  snd_hda_find_mixer_ctl (struct hda_codec*,char*) ; 
 int snd_hda_jack_add_kctls (struct hda_codec*,int /*<<< orphan*/ *) ; 

int snd_hda_gen_build_controls(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int err;

	if (spec->kctls.used) {
		err = snd_hda_add_new_ctls(codec, spec->kctls.list);
		if (err < 0)
			return err;
	}

	if (spec->multiout.dig_out_nid) {
		err = snd_hda_create_dig_out_ctls(codec,
						  spec->multiout.dig_out_nid,
						  spec->multiout.dig_out_nid,
						  spec->pcm_rec[1].pcm_type);
		if (err < 0)
			return err;
		if (!spec->no_analog) {
			err = snd_hda_create_spdif_share_sw(codec,
							    &spec->multiout);
			if (err < 0)
				return err;
			spec->multiout.share_spdif = 1;
		}
	}
	if (spec->dig_in_nid) {
		err = snd_hda_create_spdif_in_ctls(codec, spec->dig_in_nid);
		if (err < 0)
			return err;
	}

	/* if we have no master control, let's create it */
	if (!spec->no_analog &&
	    !snd_hda_find_mixer_ctl(codec, "Master Playback Volume")) {
		err = snd_hda_add_vmaster(codec, "Master Playback Volume",
					  spec->vmaster_tlv, slave_pfxs,
					  "Playback Volume");
		if (err < 0)
			return err;
	}
	if (!spec->no_analog &&
	    !snd_hda_find_mixer_ctl(codec, "Master Playback Switch")) {
		err = __snd_hda_add_vmaster(codec, "Master Playback Switch",
					    NULL, slave_pfxs,
					    "Playback Switch",
					    true, &spec->vmaster_mute.sw_kctl);
		if (err < 0)
			return err;
		if (spec->vmaster_mute.hook)
			snd_hda_add_vmaster_hook(codec, &spec->vmaster_mute,
						 spec->vmaster_mute_enum);
	}

	free_kctls(spec); /* no longer needed */

	err = snd_hda_jack_add_kctls(codec, &spec->autocfg);
	if (err < 0)
		return err;

	return 0;
}