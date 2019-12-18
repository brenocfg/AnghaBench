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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  dc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  conexant_init (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_enable_dc (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_hp_automute (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_olpc_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_set_mic_boost (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int cxt5066_olpc_init(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	snd_printdd("CXT5066: init\n");
	conexant_init(codec);
	cxt5066_hp_automute(codec);
	if (!spec->dc_enable) {
		cxt5066_set_mic_boost(codec);
		cxt5066_olpc_automic(codec);
	} else {
		cxt5066_enable_dc(codec);
	}
	return 0;
}