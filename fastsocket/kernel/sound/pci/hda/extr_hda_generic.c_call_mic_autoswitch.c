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
struct hda_jack_tbl {int dummy; } ;
struct hda_gen_spec {int /*<<< orphan*/  (* mic_autoswitch_hook ) (struct hda_codec*,struct hda_jack_tbl*) ;} ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_gen_mic_autoswitch (struct hda_codec*,struct hda_jack_tbl*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct hda_jack_tbl*) ; 

__attribute__((used)) static void call_mic_autoswitch(struct hda_codec *codec,
				struct hda_jack_tbl *jack)
{
	struct hda_gen_spec *spec = codec->spec;
	if (spec->mic_autoswitch_hook)
		spec->mic_autoswitch_hook(codec, jack);
	else
		snd_hda_gen_mic_autoswitch(codec, jack);
}