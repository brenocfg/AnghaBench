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
struct hda_codec {struct alc_spec* spec; } ;
struct auto_pin_cfg {int dummy; } ;
struct TYPE_2__ {struct auto_pin_cfg autocfg; } ;
struct alc_spec {int /*<<< orphan*/  parse_flags; TYPE_1__ gen; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  alc_ssid_check (struct hda_codec*,int /*<<< orphan*/  const*) ; 
 int snd_hda_gen_parse_auto_config (struct hda_codec*,struct auto_pin_cfg*) ; 
 int snd_hda_parse_pin_defcfg (struct hda_codec*,struct auto_pin_cfg*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alc_parse_auto_config(struct hda_codec *codec,
				 const hda_nid_t *ignore_nids,
				 const hda_nid_t *ssid_nids)
{
	struct alc_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->gen.autocfg;
	int err;

	err = snd_hda_parse_pin_defcfg(codec, cfg, ignore_nids,
				       spec->parse_flags);
	if (err < 0)
		return err;

	if (ssid_nids)
		alc_ssid_check(codec, ssid_nids);

	err = snd_hda_gen_parse_auto_config(codec, cfg);
	if (err < 0)
		return err;

	return 1;
}