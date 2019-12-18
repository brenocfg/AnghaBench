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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  hp_automute_hook; } ;
struct alc_spec {TYPE_1__ gen; int /*<<< orphan*/  parse_flags; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_PINCFG_HEADSET_MIC ; 
 int /*<<< orphan*/  alc269_x101_hp_automute_hook ; 

__attribute__((used)) static void alc269_fixup_x101_headset_mic(struct hda_codec *codec,
				     const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->parse_flags |= HDA_PINCFG_HEADSET_MIC;
		spec->gen.hp_automute_hook = alc269_x101_hp_automute_hook;
	}
}