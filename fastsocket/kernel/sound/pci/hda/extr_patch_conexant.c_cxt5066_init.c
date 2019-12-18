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
struct TYPE_2__ {scalar_t__ unsol_event; } ;
struct hda_codec {TYPE_1__ patch_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  conexant_init (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_hp_automute (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_set_mic_boost (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int cxt5066_init(struct hda_codec *codec)
{
	snd_printdd("CXT5066: init\n");
	conexant_init(codec);
	if (codec->patch_ops.unsol_event) {
		cxt5066_hp_automute(codec);
		cxt5066_automic(codec);
	}
	cxt5066_set_mic_boost(codec);
	return 0;
}