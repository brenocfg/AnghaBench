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
struct hda_codec {struct cs_spec* spec; } ;
struct auto_pin_cfg {int dig_outs; int /*<<< orphan*/ * dig_out_pins; } ;
struct TYPE_2__ {struct auto_pin_cfg autocfg; } ;
struct cs_spec {int spdif_detect; TYPE_1__ gen; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_WCAP_UNSOL_CAP ; 
 int /*<<< orphan*/  SPDIF_EVENT ; 
 int /*<<< orphan*/  cs4210_spdif_automute ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_cs421x_digital(struct hda_codec *codec)
{
	struct cs_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->gen.autocfg;
	int i;

	for (i = 0; i < cfg->dig_outs; i++) {
		hda_nid_t nid = cfg->dig_out_pins[i];
		if (get_wcaps(codec, nid) & AC_WCAP_UNSOL_CAP) {
			spec->spdif_detect = 1;
			snd_hda_jack_detect_enable_callback(codec, nid,
							    SPDIF_EVENT,
							    cs4210_spdif_automute);
		}
	}
}