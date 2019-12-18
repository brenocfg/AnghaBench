#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hda_jack_tbl {scalar_t__ jack; } ;
struct TYPE_4__ {int used; struct hda_jack_tbl* list; } ;
struct hda_codec {TYPE_2__ jacktbl; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_array_free (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,scalar_t__) ; 

void snd_hda_jack_tbl_clear(struct hda_codec *codec)
{
#ifdef CONFIG_SND_HDA_INPUT_JACK
	/* free jack instances manually when clearing/reconfiguring */
	if (!codec->bus->shutdown && codec->jacktbl.list) {
		struct hda_jack_tbl *jack = codec->jacktbl.list;
		int i;
		for (i = 0; i < codec->jacktbl.used; i++, jack++) {
			if (jack->jack)
				snd_device_free(codec->bus->card, jack->jack);
		}
	}
#endif
	snd_array_free(&codec->jacktbl);
}