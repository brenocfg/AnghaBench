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
struct hda_codec {struct ad198x_spec* spec; } ;
struct ad198x_spec {int /*<<< orphan*/  eapd_nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_EAPD_BTLENABLE ; 
 int /*<<< orphan*/  snd_hda_codec_update_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ad_vmaster_eapd_hook(void *private_data, int enabled)
{
	struct hda_codec *codec = private_data;
	struct ad198x_spec *spec = codec->spec;

	if (!spec->eapd_nid)
		return;
	snd_hda_codec_update_cache(codec, spec->eapd_nid, 0,
				   AC_VERB_SET_EAPD_BTLENABLE,
				   enabled ? 0x02 : 0x00);
}