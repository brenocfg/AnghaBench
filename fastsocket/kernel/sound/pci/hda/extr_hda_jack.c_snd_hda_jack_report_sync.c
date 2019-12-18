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
struct hda_jack_tbl {int /*<<< orphan*/  type; scalar_t__ jack; int /*<<< orphan*/  kctl; int /*<<< orphan*/  pin_sense; scalar_t__ nid; } ;
struct TYPE_3__ {int used; struct hda_jack_tbl* list; } ;
struct hda_codec {TYPE_2__* bus; TYPE_1__ jacktbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int get_jack_plug_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_detect_update (struct hda_codec*,struct hda_jack_tbl*) ; 
 int /*<<< orphan*/  snd_jack_report (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_kctl_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void snd_hda_jack_report_sync(struct hda_codec *codec)
{
	struct hda_jack_tbl *jack;
	int i, state;

	/* update all jacks at first */
	jack = codec->jacktbl.list;
	for (i = 0; i < codec->jacktbl.used; i++, jack++)
		if (jack->nid)
			jack_detect_update(codec, jack);

	/* report the updated jacks; it's done after updating all jacks
	 * to make sure that all gating jacks properly have been set
	 */
	jack = codec->jacktbl.list;
	for (i = 0; i < codec->jacktbl.used; i++, jack++)
		if (jack->nid) {
			if (!jack->kctl)
				continue;
			state = get_jack_plug_state(jack->pin_sense);
			snd_kctl_jack_report(codec->bus->card, jack->kctl, state);
#ifdef CONFIG_SND_HDA_INPUT_JACK
			if (jack->jack)
				snd_jack_report(jack->jack,
						state ? jack->type : 0);
#endif
		}
}