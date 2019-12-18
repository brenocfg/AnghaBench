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
struct nid_path {int depth; int /*<<< orphan*/ * path; scalar_t__ active; } ;
struct hda_gen_spec {int /*<<< orphan*/  power_down_unused; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_GET_POWER_STATE ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  is_active_nid_for_any (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_check_power_state (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_power_down_sync(struct hda_codec *codec, struct nid_path *path)
{
	struct hda_gen_spec *spec = codec->spec;
	bool changed = false;
	int i;

	if (!spec->power_down_unused || path->active)
		return;

	for (i = 0; i < path->depth; i++) {
		hda_nid_t nid = path->path[i];
		if (!snd_hda_check_power_state(codec, nid, AC_PWRST_D3) &&
		    !is_active_nid_for_any(codec, nid)) {
			snd_hda_codec_write(codec, nid, 0,
					    AC_VERB_SET_POWER_STATE,
					    AC_PWRST_D3);
			changed = true;
		}
	}

	if (changed) {
		msleep(10);
		snd_hda_codec_read(codec, path->path[0], 0,
				   AC_VERB_GET_POWER_STATE, 0);
	}
}